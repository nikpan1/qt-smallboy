
#define _DEBUG(x) ui->log->setText(x); 

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define _WARNING(desc) message(__FILE__ "(" TOSTRING(__LINE__) ") : warning: " #desc)
  