#include <wlog/init.hpp>                                                                                                                                                                
#include <wlog/load.hpp>                                                                                                                                                                
#include <iostream>

int main()
{
  // По умолчанию вывод только в clog в цвете
  wlog::init();
  // Выводить с тысячными долями секунд и отключить цветовую раскраску 
  wlog::init(wlog::resolutions::milliseconds, wlog::colorized_flags::none);
  // Выводить в файл и clog
  wlog::init("main.log");
  // Выводить с тысячными долями секунд в файл и clog и отключить цветовую раскраску для clog
  wlog::init("main.log", wlog::resolutions::milliseconds, wlog::colorized_flags::none);

  // Так можно задать все остальные опции
  wlog::logger_options opt;
  opt.path="main.log";
  wlog::init(opt);

  // Загрузть конфигурацию из файла
  wlog::init(wlog::load("logger.json"));
  // Загрузть конфигурацию из строки
  wlog::init(wlog::load("{\"path\":\"main.log\"}"));
  
  // Вариант с проверкой 
  std::string err;
  opt = wlog::logger_options();
  if ( wlog::load("logger.json", &opt, &err) )
    wlog::init(opt);
  else
    std::cerr << "ERROR: " << err << std::endl;
  
  // Выключаем логгирование 
  if (auto log = wlog::release() )
  {
    // Глобальный лог уже не доступен
    // Но можем записать в лог финальное сообщение
    log( wlog::time_point::clock::now(), "EXAMPLE4", "FINAL", "Bye!\n" );
  }
}
