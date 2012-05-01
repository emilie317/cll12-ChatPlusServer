#ifndef CHATPLUSSERVER_H
#define CHATPLUSSERVER_H

#include <QMainWindow>

namespace Ui {
class ChatPlusServer;
}

class ChatPlusServer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ChatPlusServer(QWidget *parent = 0);
    ~ChatPlusServer();
    
private:
    Ui::ChatPlusServer *ui;
};

#endif // CHATPLUSSERVER_H
