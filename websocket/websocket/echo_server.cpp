

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

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
	std::cout << "on_message called with hdl: " << hdl.lock().get() << std::endl
              << " and message: " << msg->get_payload()
              << std::endl;

    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
    if (msg->get_payload() == "stop-listening") {
        s->stop_listening();
        return;
    }
	std::string mstr = websocketpp::base64_decode(msg->get_payload());
	int len = mstr.length();
	byte* imgbuffer = new byte[len];
	for (int i = 0; i < len;i++)
	{
		imgbuffer[i] = mstr[i];
	}
	//memcpy(imgbuffer, mstr.data(), len);
	int imagesize = len / 3;
	Mat mMat(2, &imagesize, CV_8UC3, imgbuffer);
	//CImage mimg(imgbuffer,len, CXIMAGE_FORMAT_JPG)
	try
	{
		imshow("½ÓÊÕ", mMat);
	}
	catch (...)
	{
		std::cout << "image error!" << std::endl;
	}
	
    try {
        s->send(hdl, std::string("Received your message!")/*msg->get_payload()*/, websocketpp::frame::opcode::text/*msg->get_opcode()*/);
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
                  << "(" << e.message() << ")" << std::endl;
    }
}

int main() {
	/*
     //Create a server endpoint
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
	*/
	
	CDatabaseManager mDbm;
	vector<pair<RelicObj, ObjInfo>> RelicObjVec;
	mDbm.initial();
	mDbm.ConnectDb();
	if (mDbm.m_DbStatus== CDatabaseManager::DB_CONNECT)
	{
		mDbm.LoadFromDb(RelicObjVec);
	}
	
	return 0;
}
