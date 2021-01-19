#include "QSlipCreate.h"
#pragma execution_character_set("utf-8")
QSlipCreate::QSlipCreate()
{
	m_tscdll = nullptr;
	m_bDllIsLoad = false;
	m_tscdll = new QLibrary("TSCLIB.dll");
	if (m_tscdll)
	{
		m_bDllIsLoad = m_tscdll->load();
	}
}

QSlipCreate::~QSlipCreate()
{
	delete m_tscdll;
}

void QSlipCreate::GetLastMsg(int type, QString& Msg)
{
	switch (type)
	{
	case GENERATE_ERR_::GenerateSlip_OK:
		Msg = "标签图像生成成功!";
		break;
	case GENERATE_ERR_::GenerateQRcode_failed:
		Msg = "二维码生成失败!";
		break;
	case GENERATE_ERR_::CreateSlipInfo_failed:
		Msg = "封签信息生成失败!";
		break;
	case GENERATE_ERR_::Save_image_failed:
		Msg = "存储失败!";
		break;
	case GENERATE_ERR_::Load_ModelImg_failed:
		Msg = "加载模板图像失败!";
		break;
	case GENERATE_ERR_::Create_FQimg_failed:
		Msg = "生成封签图像失败!";
		break;
	default:
		Msg = "";
		break;
	}
}
void QSlipCreate::SetPath(QString model_path, QString print_path)
{
	m_modelPath = model_path;
	m_printPath = print_path;
	m_modelImg = cv::imread(m_modelPath.toStdString(), 0);
}

void QSlipCreate::GetPath(QString& model_path, QString& print_path)
{
	model_path = m_modelPath;
	print_path = m_printPath;
}

bool QSlipCreate::GenerateQRcode(QString QRtempstr, cv::Mat& img)
{
	if (QRtempstr == "")
	{
		return false;
	}
	QRcode *qrcode;
	qrcode = QRcode_encodeString(QRtempstr.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
	qint32 temp_width = 180;
	qint32 temp_height = 180;
	qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
	double scale_x = (double)temp_width / (double)qrcode_width;
	double scale_y = (double)temp_height / (double)qrcode_width;
	QImage mainimg = QImage(temp_width, temp_height, QImage::Format_ARGB32);
	QPainter painter(&mainimg);
	QColor background(Qt::white);
	painter.setBrush(background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, temp_width, temp_height);
	QColor foreground(Qt::black);
	painter.setBrush(foreground);
	for (qint32 y = 0; y < qrcode_width; y++)
	{
		for (qint32 x = 0; x < qrcode_width; x++)
		{
			unsigned char b = qrcode->data[y*qrcode_width + x];
			if (b & 0x01)
			{
				QRectF r(x*scale_x, y*scale_y, scale_x, scale_y);
				painter.drawRects(&r, 1);
			}
		}
	}

	switch (mainimg.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		m_QRmat = cv::Mat(mainimg.height(), mainimg.width(), CV_8UC4, (void*)mainimg.constBits(), mainimg.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		m_QRmat = cv::Mat(mainimg.height(), mainimg.width(), CV_8UC3, (void*)mainimg.constBits(), mainimg.bytesPerLine());
		cv::cvtColor(m_QRmat, m_QRmat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		m_QRmat = cv::Mat(mainimg.height(), mainimg.width(), CV_8UC1, (void*)mainimg.constBits(), mainimg.bytesPerLine());
		break;
	}
	cv::cvtColor(m_QRmat, m_QRmat, CV_BGR2GRAY);//转为灰度图
	img = m_QRmat;
	return true;
}

int QSlipCreate::GenerateSlipInfo(SLIP_PRINT_INFO slip_info, cv::Mat& img)
{
	if (m_modelImg.empty())
	{
		return GENERATE_ERR_::Load_ModelImg_failed;
	}
	cv::Mat QRimg;
	if (!GenerateQRcode(slip_info.QRStr, QRimg))
	{
		return GENERATE_ERR_::GenerateQRcode_failed;
	}
	if (QRimg.empty())
	{
		return GENERATE_ERR_::GenerateQRcode_failed;
	}
	QString Coupons;
	QString NumCoupons = slip_info.QBInfo;
	cv::Point Numpoint;
	bool bInfo = true;
	switch (slip_info.QBInfo.toInt())
	{
	case PRODECT_COUPONS_::One_yuan:
		Coupons = "壹圆券";
		Numpoint = cv::Point(115, 75);
		break;
	case PRODECT_COUPONS_::Five_yuan:
		Coupons = "伍圆券";
		Numpoint = cv::Point(115, 75);
		break;
	case PRODECT_COUPONS_::Ten_yuan:
		Coupons = "拾圆券";
		Numpoint = cv::Point(95, 75);
		break;
	case PRODECT_COUPONS_::Twenty_yuan:
		Coupons = "贰拾圆券";
		Numpoint = cv::Point(95, 75);
		break;
	case PRODECT_COUPONS_::Fifty_yuan:
		Coupons = "伍拾圆券";
		Numpoint = cv::Point(95, 75);
		break;
	case PRODECT_COUPONS_::One_hundred_yuan:
		Coupons = "壹佰圆券";
		Numpoint = cv::Point(70, 75);
		break;
	default:
		bInfo = false;
		break;
	}
	if (!bInfo)
	{
		return GENERATE_ERR_::CreateSlipInfo_failed;
	}

	cv::Mat imageROI;
	m_SlipImg = m_modelImg.clone();
// 	imageROI = m_SlipImg(cv::Rect(70, 250, QRimg.cols, QRimg.rows));
// 	cv::Mat mask = QRimg;
// 	QRimg.copyTo(imageROI);
// 	if (m_SlipImg.empty())
// 	{
// 		return GENERATE_ERR_::Create_FQimg_failed;
// 	}
	QByteArray array;
	array = Coupons.toLocal8Bit();
	char *Couchar = array.data();
	putTextZH(m_SlipImg, Couchar, cv::Point(310, 270), cv::Scalar(0, 0, 0), 40, "Arial", false, false);
	putTextZH(m_SlipImg, Couchar, cv::Point(880, 270), cv::Scalar(0, 0, 0), 40, "Arial", false, false);

	if (!slip_info.FHInfo.isEmpty())
	{
		array = slip_info.FHInfo.toLocal8Bit();
		char *FHInfochar = array.data();
		putTextZH(m_SlipImg, FHInfochar, cv::Point(180, 460), cv::Scalar(0, 0, 0), 40, "Arial");
	}
	if (!slip_info.FHInfo2.isEmpty())
	{
		array = slip_info.FHInfo2.toLocal8Bit();
		char *FH2Infochar = array.data();
		putTextZH(m_SlipImg, FH2Infochar, cv::Point(430, 460), cv::Scalar(0, 0, 0), 40, "Arial");
	}
	if (!slip_info.FQInfo.isEmpty())
	{
		array = slip_info.FQInfo.toLocal8Bit();
		char *FQInfochar = array.data();
		putTextZH(m_SlipImg, FQInfochar, cv::Point(870, 460), cv::Scalar(0, 0, 0), 40, "Arial");
	}

	array = slip_info.date.toLocal8Bit();
	char *datechar = array.data();
	putTextZH(m_SlipImg, datechar, cv::Point(180, 566), cv::Scalar(0, 0, 0), 40, "Arial");
	putTextZH(m_SlipImg, datechar, cv::Point(870, 570), cv::Scalar(0, 0, 0), 30, "Arial");

	if (!save_bmp_image(m_SlipImg, m_printPath.toStdString()))
	{
		return GENERATE_ERR_::Save_image_failed;
	}
	img = m_SlipImg;
	return GENERATE_ERR_::GenerateSlip_OK;
}

bool QSlipCreate::PrePrint(cv::Mat& img)
{
	if (m_SlipImg.empty())
	{
		return false;
	}
	img = m_SlipImg;
	return true;
}

bool QSlipCreate::Print()
{

	typedef int(*TSCabout)();
	typedef int(*TSCopenport)(char*);
	typedef int(*TSCsendcommand)(char*);
	typedef int(*TSCcloseport)();
	typedef int(*TSCdownloadbmp)(char*, char*);


	TSCabout about = (TSCabout)m_tscdll->resolve("about");
	TSCopenport openport = (TSCopenport)m_tscdll->resolve("openport");
	TSCcloseport closeport = (TSCcloseport)m_tscdll->resolve("closeport");
	TSCsendcommand sendcommand = (TSCsendcommand)m_tscdll->resolve("sendcommand");
	TSCdownloadbmp downloadbmp = (TSCdownloadbmp)m_tscdll->resolve("downloadbmp");

	openport("TSC TTP-345");
	sendcommand("SIZE 104.1 mm. 59.4 mm");
	sendcommand("SPEED 2");
	sendcommand("DIRECTION 1");
	sendcommand("DENSITY 3 ");
	sendcommand("GAP 0.1, 0");
	sendcommand("CLS");
	char* ch;
	QByteArray ba = m_printPath.toLatin1();
	ch = ba.data();
	downloadbmp(ch, "print.bmp");
	sendcommand("PUTBMP 20,20,\"print.bmp\",1,80");
	sendcommand("PRINT 1");
	closeport();
	return true;
}

int QSlipCreate::GetPrintStatus(void)
{
	typedef int(*UsbPortQueryPrinter)();
	UsbPortQueryPrinter usbportqueryprinter = (UsbPortQueryPrinter)m_tscdll->resolve("usbportqueryprinter");
	return usbportqueryprinter();
}

bool QSlipCreate::LoadDllStatus(void)
{
	return m_bDllIsLoad;
}

void QSlipCreate::putTextZH(cv::Mat &dst, const char* str, cv::Point org, cv::Scalar color, int fontSize, const char *fn /*= "Arial"*/, bool italic /*= false*/, bool underline /*= false*/)
{
	CV_Assert(dst.data != 0 && (dst.channels() == 1 || dst.channels() == 3));

	int x, y, r, b;
	if (org.x > dst.cols || org.y > dst.rows) return;
	x = org.x < 0 ? -org.x : 0;
	y = org.y < 0 ? -org.y : 0;

	LOGFONTA lf;
	lf.lfHeight = -fontSize;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 5;
	lf.lfItalic = italic;   //斜体
	lf.lfUnderline = underline; //下划线
	lf.lfStrikeOut = 0;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = 0;
	strcpy_s(lf.lfFaceName, fn);

	HFONT hf = CreateFontIndirectA(&lf);
	HDC hDC = CreateCompatibleDC(0);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hf);

	int strBaseW = 0, strBaseH = 0;
	int singleRow = 0;
	char buf[1 << 12];
	strcpy_s(buf, str);
	char *bufT[1 << 12];  // 这个用于分隔字符串后剩余的字符，可能会超出。
	//处理多行
	{
		int nnh = 0;
		int cw = 0, ch = 0;

		const char* ln = strtok_s(buf, "\n", bufT);
		while (ln != 0)
		{
			SIZE size;
			GetTextExtentPoint32A(hDC, ln, strlen(ln), &size);
			cw = size.cx;
			ch = size.cy;

			strBaseW = max(strBaseW, cw);
			strBaseH = max(strBaseH, ch);

			ln = strtok_s(0, "\n", bufT);
			nnh++;
		}
		singleRow = strBaseH;
		strBaseH *= nnh;
	}

	if (org.x + strBaseW < 0 || org.y + strBaseH < 0)
	{
		SelectObject(hDC, hOldFont);
		DeleteObject(hf);
		DeleteObject(hDC);
		return;
	}

	r = org.x + strBaseW > dst.cols ? dst.cols - org.x - 1 : strBaseW - 1;
	b = org.y + strBaseH > dst.rows ? dst.rows - org.y - 1 : strBaseH - 1;
	org.x = org.x < 0 ? 0 : org.x;
	org.y = org.y < 0 ? 0 : org.y;

	BITMAPINFO bmp = { 0 };
	BITMAPINFOHEADER& bih = bmp.bmiHeader;
	int strDrawLineStep = strBaseW * 3 % 4 == 0 ? strBaseW * 3 : (strBaseW * 3 + 4 - ((strBaseW * 3) % 4));

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = strBaseW;
	bih.biHeight = strBaseH;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = strBaseH * strDrawLineStep;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	void* pDibData = 0;
	HBITMAP hBmp = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, &pDibData, 0, 0);

	CV_Assert(pDibData != 0);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);

	//color.val[2], color.val[1], color.val[0]
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, 0);
	//SetStretchBltMode(hDC, COLORONCOLOR);

	strcpy_s(buf, str);
	const char* ln = strtok_s(buf, "\n", bufT);
	int outTextY = 0;
	while (ln != 0)
	{
		TextOutA(hDC, 0, outTextY, ln, strlen(ln));
		outTextY += singleRow;
		ln = strtok_s(0, "\n", bufT);
	}
	uchar* dstData = (uchar*)dst.data;
	int dstStep = dst.step / sizeof(dstData[0]);
	unsigned char* pImg = (unsigned char*)dst.data + org.x * dst.channels() + org.y * dstStep;
	unsigned char* pStr = (unsigned char*)pDibData + x * 3;
	for (int tty = y; tty <= b; ++tty)
	{
		unsigned char* subImg = pImg + (tty - y) * dstStep;
		unsigned char* subStr = pStr + (strBaseH - tty - 1) * strDrawLineStep;
		for (int ttx = x; ttx <= r; ++ttx)
		{
			for (int n = 0; n < dst.channels(); ++n) {
				double vtxt = subStr[n] / 255.0;
				int cvv = vtxt * color.val[n] + (1 - vtxt) * subImg[n];
				subImg[n] = cvv > 255 ? 255 : (cvv < 0 ? 0 : cvv);
			}

			subStr += 3;
			subImg += dst.channels();
		}
	}

	SelectObject(hDC, hOldBmp);
	SelectObject(hDC, hOldFont);
	DeleteObject(hf);
	DeleteObject(hBmp);
	DeleteDC(hDC);
}

bool QSlipCreate::save_bmp_image(const cv::Mat img, std::string dst)
{
	int  width = img.cols;
	int  height = img.rows;
	const  int  biBitCount = 1;

	//颜色表大小，以字节为单位，灰度图像颜色表为256*4字节，彩色图像颜色表大小为0,二值图为2*4
	int  color_type_num = 2;
	int  colorTablesize = color_type_num * sizeof(RGBQUAD);
	RGBQUAD *pColorTable = new  RGBQUAD[color_type_num];
	for (int i = 0; i < color_type_num; i++) {
		pColorTable[i].rgbBlue = i * 255;
		pColorTable[i].rgbRed = i * 255;
		pColorTable[i].rgbGreen = i * 255;
		pColorTable[i].rgbReserved = 0;
	}

	//待存储图像数据每行字节数为4的倍数
	int  line_byte = (width * biBitCount / 8 + 3) / 4 * 4;
	char * p_data = (char *)malloc(line_byte*height);
	mat_to_binary(img, line_byte, p_data);

	std::ofstream fp(dst.c_str(), std::ios::binary | std::ios::out);

	if (!fp.is_open()) {
		std::cout << "open " << dst << " failed!" << std::endl;
		return  false;
	}

	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;   //bmp类型

	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)\
		+ colorTablesize + line_byte*height;               //bfSize是图像文件4个组成部分之和
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits = 54 + colorTablesize;               //bfOffBits是图像文件前3个部分所需空间之和    

	fp.write((char *)&fileHead, sizeof(BITMAPFILEHEADER)); //写文件头进文件

	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = line_byte*height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;

	//写位图信息头进内存  
	fp.write((char *)&head, sizeof(BITMAPINFOHEADER));

	//颜色表，写入文件 
	fp.write((char *)pColorTable, sizeof(RGBQUAD)*color_type_num);

	//写位图数据进文件pBmpBuf
	fp.write((char *)p_data, height*line_byte);
	fp.close();

	delete[]pColorTable;
	delete[]p_data;
	return true;
}

int QSlipCreate::mat_to_binary(const cv::Mat img, int line_byte, char * data)
{
	int  width = img.cols;
	int  height = img.rows;
	size_t  line_size = line_byte * 8;
	size_t  bit_size = line_size * height;

	char  *p = data;  int  offset, v; unsigned  char  temp;
	for (int row = height - 1; row >= 0; row--) {
		for (int col = 0; col < width; col++) {
			offset = col % 8;
			v = img.at<uchar>(row, col);
			temp = 1;
			temp = temp << (8 - offset - 1);
			if (v == 255) {
				*(p + col / 8) |= temp;
			}
			else {
				temp = ~temp;
				*(p + col / 8) &= temp;
			}
		}
		for (int j = width / 8; j < line_byte; j++)
			p[j] = 0;
		p = p + line_byte;
	}
	return  0;
}
QKXSlipCreate * _stdcall QKXSlipCreateInstance(int version)
{
	if (version == KX_KXSLIP_CREATE_VERSION)
	{

		auto p = new QSlipCreate;
		if (p->LoadDllStatus())
		{
			return p;
		}
		else
		{
			delete p;
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}
