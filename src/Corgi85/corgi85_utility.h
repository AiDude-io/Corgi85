#include <map>
#include <vector>
#ifndef CORGI85_UTILITY_H
#define CORGI85_UTILITY_H
#define MAXLENGTH 255

#include "modules/CorgiModule.h"
typedef void (*Callback) (std::vector<String>);
enum event
{
    emtry,
    new_event
};

//enum app
//{
//    BLYNK,
//    LINE,
//    Thingspeak,
//    Netpie,
//    IFTTT,
//    Mqtt
//};

typedef std::map<const char*, CorgiModule*> CorgiModulesMap;

class CORGI85
{
public:
    uint8_t receivedFlag;
    // uint8_t run(void);
    uint8_t loop(void);
    CORGI85(HardwareSerial *Serial);
    event check_event();
    bool addModule(CorgiModule *module);
    void printModulesList();

private:
    Stream *corgi_serial;

    std::map<String, Callback> registered_callback;

    uint8_t pointer_head = 0;
    uint8_t pointer_tail = 0;

    uint8_t raw_buffer_ring[MAXLENGTH];
    uint8_t decode_buffer[MAXLENGTH];

    uint8_t checkSum(uint8_t array[], uint8_t length);
    uint8_t buffer_avaliable(void);
    CorgiModulesMap moduleList;

    String _raw ="";
    String _data_="";
};

#endif
