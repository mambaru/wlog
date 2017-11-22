//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/global_log.hpp>

namespace wlog{
  
template<typename ...Args>
inline void only_for_log( Args&& ... ){}

}

#ifndef WLOG_DISABLE_ALL_LOG
#   define WLOG_WRITE_ENDL( name, type, msg ) ::wlog::global_log(name, type) << msg << std::endl;
#   define WLOG_WRITE_ENDR( name, type, msg ) ::wlog::global_log(name, type) << msg << "\r";
#else
#   define WLOG_WRITE_ENDL(name, type, msg)
#   define WLOG_WRITE_ENDR( name, type, msg )
#endif

#define WLOG_WRITE_ERROR( name, X )         WLOG_WRITE_ENDL(name, "ERROR",   X )
#define WLOG_WRITE_WARNING( name, X )       WLOG_WRITE_ENDL(name, "WARNING", X )
#define WLOG_WRITE_MESSAGE( name, X )       WLOG_WRITE_ENDL(name, "MESSAGE", X )
#define WLOG_WRITE_FATAL( name, X )         WLOG_WRITE_ENDL(name, "FATAL",   X )
#define WLOG_WRITE_BEGIN( name, X )         WLOG_WRITE_ENDL(name, "BEGIN",   X )
#define WLOG_WRITE_END( name, X )           WLOG_WRITE_ENDL(name, "END",   X )
#define WLOG_WRITE_PROGRESS( name, X )      WLOG_WRITE_ENDR(name, "PROGRESS",   X )

#ifdef NDEBUG 
# ifdef WLOG_ENABLE_DEBUG_LOG          // включить в Release режиме
#   define WLOG_WRITE_DEBUG( name, X )      WLOG_WRITE_ENDL(name, "DEBUG",   X )
#   define WLOG_WRITE_TRACE( name, X )      WLOG_WRITE_ENDL(name, "TRACE",   X )
# else
#   define WLOG_WRITE_DEBUG( name, X )
#   define WLOG_WRITE_TRACE( name, X )         
# endif
#else
# ifdef WLOG_DISABLE_DEBUG_LOG         // отключить в Debug режиме
#   define WLOG_WRITE_DEBUG( name, X )
#   define WLOG_WRITE_TRACE( name, X )         
# else
#   define WLOG_WRITE_DEBUG( name, X )      WLOG_WRITE_ENDL(name, "DEBUG",   X )
#   define WLOG_WRITE_TRACE( name, X )      WLOG_WRITE_ENDL(name, "TRACE",   X )
# endif
#endif


#define WLOG_ERROR(X)    WLOG_WRITE_ERROR( "WLOG", X )
#define WLOG_WARNING(X)  WLOG_WRITE_WARNING( "WLOG", X )
#define WLOG_MESSAGE(X)  WLOG_WRITE_MESSAGE( "WLOG", X )
#define WLOG_FATAL(X)    WLOG_WRITE_FATAL( "WLOG", X )
#define WLOG_BEGIN(X)    WLOG_WRITE_BEGIN( "WLOG", X )
#define WLOG_END(X)      WLOG_WRITE_END( "WLOG", X )
#define WLOG_DEBUG(X)    WLOG_WRITE_DEBUG( "WLOG", X )
#define WLOG_TRACE(X)    WLOG_WRITE_TRACE( "WLOG", X )
#define WLOG_PROGRESS(X) WLOG_WRITE_PROGRESS( "WLOG", X )

