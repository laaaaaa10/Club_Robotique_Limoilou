#ifndef GPSP_h
#define GPSP_h
#include "Arduino.h"
#include <QList.h>

typedef void (*GPSPCallBack)(Stream &stream, const char args[][50], int size);
struct Command {
    /**
     * @brief 
     * 
     */
    GPSPCallBack callback;
    char* name;
    char* description;
};
class GPSP {
    public:
        GPSP(Stream &stream);
        void defineCommand(Command command);
        void update();

        static void printError(Stream &stream, const char *errorMessage);
        Stream& getStream();

    private:
        char args_temp[10][50]; //  Used to temporarily store retrieved Arguments
        char buffer[500];
        int index = 0;
        
        void processBuffer();
        void helpCommand(const char args[][50], int size);
        void printCommand(Command command);

        Stream *stream;
        QList<Command> commandList = QList<Command>();
};

#endif
