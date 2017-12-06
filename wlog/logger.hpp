//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/global_log.hpp>

#ifndef WLOG_DISABLE_ALL_LOG
#   define WLOG( name, type, msg ) ::wlog::global_log(name, type) << msg << std::endl;
#   define WLOGR( name, type, msg ) ::wlog::global_log(name, type) << msg << "\r";
#else
#   define WLOG(name, type, msg)
#   define WLOGR( name, type, msg )
#endif

#define WLOG_LOG_ERROR( name, X )         WLOG(name,  "ERROR",   X )
#define WLOG_LOG_WARNING( name, X )       WLOG(name,  "WARNING", X )
#define WLOG_LOG_MESSAGE( name, X )       WLOG(name,  "MESSAGE", X )
#define WLOG_LOG_FATAL( name, X )         WLOG(name,  "FATAL",   X )
#define WLOG_LOG_BEGIN( name, X )         WLOG(name,  "BEGIN",   X )
#define WLOG_LOG_END( name, X )           WLOG(name,  "END",   X )
#define WLOG_LOG_PROGRESS( name, X )      WLOGR(name, "PROGRESS",   X )

#ifdef NDEBUG 
# ifdef WLOG_ENABLE_DEBUG_LOG          // включить в Release режиме
#   define WLOG_LOG_DEBUG( name, X )      WLOG(name, "DEBUG",   X )
#   define WLOG_LOG_TRACE( name, X )      WLOG(name, "TRACE",   X )
# else
#   define WLOG_LOG_DEBUG( name, X )
#   define WLOG_LOG_TRACE( name, X )         
# endif
#else
# ifdef WLOG_DISABLE_DEBUG_LOG         // отключить в Debug режиме
#   define WLOG_LOG_DEBUG( name, X )
#   define WLOG_LOG_TRACE( name, X )         
# else
#   define WLOG_LOG_DEBUG( name, X )      WLOG(name, "DEBUG",   X )
#   define WLOG_LOG_TRACE( name, X )      WLOG(name, "TRACE",   X )
# endif
#endif

#define WLOG_ERROR(X)    WLOG_LOG_ERROR   ( "WLOG", X )
#define WLOG_WARNING(X)  WLOG_LOG_WARNING ( "WLOG", X )
#define WLOG_MESSAGE(X)  WLOG_LOG_MESSAGE ( "WLOG", X )
#define WLOG_FATAL(X)    WLOG_LOG_FATAL   ( "WLOG", X )
#define WLOG_BEGIN(X)    WLOG_LOG_BEGIN   ( "WLOG", X )
#define WLOG_END(X)      WLOG_LOG_END     ( "WLOG", X )
#define WLOG_DEBUG(X)    WLOG_LOG_DEBUG   ( "WLOG", X )
#define WLOG_TRACE(X)    WLOG_LOG_TRACE   ( "WLOG", X )
#define WLOG_PROGRESS(X) WLOG_LOG_PROGRESS( "WLOG", X )
