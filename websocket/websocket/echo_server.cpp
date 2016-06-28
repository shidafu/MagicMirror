

#include "databasemanager.h"
#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>

#include <websocketpp/base64/base64.hpp>

#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv.h"


using namespace cv;
typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;
vector<pair<RelicObj, ObjInfo>> m_mObjVec1;
// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
	std::cout << "on_message called with hdl: " << hdl.lock().get()
		//<< " and message: " << msg->get_payload()
		<< std::endl;
	std::cout << "get a massage over!" << std::endl;
	vector<uchar> buff;
	string mmsg = msg->get_payload();
	cout << "srclength: " << mmsg.length() << endl;

	for (int i = 0; i < (30<mmsg.length() ? 30 : mmsg.length()); i++)
	{
		cout << mmsg[i];
	}
	cout << endl;
	size_t Offt = mmsg.find("/9j/");
	if (Offt<0)
	{
		std::cout << "Not a Base64Image!" << std::endl;
		return;
	}
	const char* Pos0 = mmsg.c_str() + Offt;
	string mmsg2 = Pos0;
	for (int i = 0; i < (30 < mmsg2.length() ? 30 : mmsg2.length()); i++)
	{
		cout << mmsg2[i];
	}
	cout << endl;
	//std::string mstr = websocketpp::base64_decode(mmsg2);
	std::string mstr1;
	try
	{
		//RelicHelper::Base64Decode(mmsg2, &mstr1);
		mstr1 = websocketpp::base64_decode(mmsg2);

		std::cout << "Base64Decode over!" << std::endl;
	}
	catch (...)
	{
		std::cout << "Base64Decode error!" << std::endl;
		return;
	}
	int len = mstr1.length();
	if (len == 0)
	{
		int a = 1;
	}
	//if (len<1000)
	//{
	//	std::cout << "Too SHort !" << std::endl;
	//	return;
	//}
	std::cout << "Length: " << len << std::endl;
	byte* imgbuffer = new byte[len];
	for (int i = 0; i < len; i++)
	{
		buff.push_back(mstr1[i]);
	}
	//memcpy(imgbuffer, mstr.data(), len);
	Mat mMat;
	try
	{
		mMat = cv::imdecode(buff, CV_LOAD_IMAGE_COLOR);
		std::cout << "imdecode over!" << std::endl;
	}
	catch (...)
	{
		std::cout << "imdecode error!" << std::endl;
		return;
	}
	try
	{
		imshow("½ÓÊÕ", mMat);
		waitKey();
	}
	catch (...)
	{
		std::cout << "image error!" << std::endl;
		return;
	}

	string Jstr;
	try
	{
		Jstr = RelicAPI::detect(mMat, m_mObjVec1);
		std::cout << "detect over!" << std::endl;
	}
	catch (...)
	{
		std::cout << "detect error!" << std::endl;
		return;
	}
	//int imagesize = len / 3;
	//Mat mMat(2, &imagesize, CV_8UC3, imgbuffer);
	//CImage mimg(imgbuffer,len, CXIMAGE_FORMAT_JPG)

	cout << Jstr << endl;
	try {
		s->send(hdl, Jstr/*msg->get_payload()*/, websocketpp::frame::opcode::text/*msg->get_opcode()*/);
	}
	catch (const websocketpp::lib::error_code& e) {
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}
}

int main() {
	
     //Create a server endpoint
	CDatabaseManager mDb;
	mDb.initial();
	mDb.ConnectDb();
	if (mDb.m_DbStatus == CDatabaseManager::DB_CONNECT)
	{
		cout << "database connect ok!" << endl;
	}
	else
	{
		cout << "database connect fail!" << endl;
		return 0;
	}
	mDb.LoadFromDb(m_mObjVec1);

	cout << "loaded elements num: " << m_mObjVec1.size() << endl;


    server echo_server;

    try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));

		//echo_server
        // Listen on port 9002
        echo_server.listen(9002);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }

	
	return 0;
}
