/* ESE 519 Project : TURF
This function is used for sending data using serial communication on xbee */
 #include "XBee.h"


XBee::XBee(PinName tx, PinName rx, PinName reset)
{
    _tx = tx;
    _rx = rx;
    _reset = reset;
}

XBee::~XBee()
{
}

int XBee::configMode()
{
    int a;
    Serial DATA(_tx,_rx);
    wait(2);
    DATA.printf("+++");
    while (a != 75) {
        if (DATA.readable()) {
            a = DATA.getc();
        }
    }
    wait(1);
    printf("config mode\n");
    return 1;
}

int XBee::getSerial(int *serial_no)
{
    int sh1,sh2,sh3,sl1,sl2,sl3,sl4;
    Serial DATA(_tx,_rx);
    wait_ms(50);
    DATA.printf("ATSL \r");
    DATA.scanf ("%2x%2x%2x%2x",&sl1,&sl2,&sl3,&sl4);
    wait_ms(500);
    DATA.printf("ATSH \r");
    DATA.scanf ("%2x%2x%2x",&sh1,&sh2,&sh3);

    serial_no[0] = sh1;
    serial_no[1] = sh2;
    serial_no[2] = sh3;
    serial_no[3] = sl1;
    serial_no[4] = sl2;
    serial_no[5] = sl3;
    serial_no[6] = sl4;

    return 1;
}

int XBee::setKey(int* key)
{
    Serial DATA(_tx,_rx);
    DATA.printf("ATEE 1 \r");

    DATA.scanf ("%*s");
    wait_ms(1);
    DATA.printf("ATKY %x \r",key);
    DATA.scanf ("%*s");
    return 1;
}

int XBee::writeSettings()
{
    Serial DATA(_tx,_rx);
    wait_ms(5);
    DATA.printf("ATWR \r");
    DATA.scanf ("%*s");
    return 1;
}

int XBee::exitConfigMode()
{
    Serial DATA(_tx,_rx);
    wait_ms(5);
    DATA.printf("ATCN \r");
    DATA.scanf ("%*s");
    return 1;
}

int XBee::sendData(string data_buf)
{
    Serial DATA(_tx,_rx);
    DATA.printf("%s",data_buf);
    return 1;
}

void XBee::recieveData(string data_buf, int numchar)
{
    int count=0;
    if(numchar == 0) {
        numchar = sizeof(data_buf);
    }
    Serial DATA(_tx,_rx);
    while(numchar!=count) {
        if(DATA.readable()) {
            data_buf+= DATA.getc();
//            data_buf+=1;
            count++;
        }

    }
}

int XBee::setPanID(int pan_id)
{
    Serial DATA(_tx,_rx);
    wait_ms(5);
    DATA.printf("ATID %i\r",pan_id);
    DATA.scanf ("%*s");
    return 1;
}

void XBee::reset()
{
    DigitalOut rssi(_reset);
    rssi = 0;
    wait_ms(10);
    rssi = 1;
    wait_ms(1);
}

void XBee::setBaud(int baudRate){
    
    
}
