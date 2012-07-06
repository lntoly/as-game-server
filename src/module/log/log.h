/*
 * log.h
 *
 *  Created on: 2012-7-4
 *      Author: Administrator
 */

#ifndef LOG_H_
#define LOG_H_

void log_print(const char*, ...);
void log_file(const char*, const char*, ...);

#define log_debug(fmt, arg...) log_file("log/debug.log", fmt, ##arg)

#endif /* LOG_H_ */
