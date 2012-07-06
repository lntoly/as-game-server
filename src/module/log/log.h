/*
 * log.h
 *
 *  Created on: 2012-7-4
 *      Author: Administrator
 */

#ifndef LOG_H_
#define LOG_H_

void log_print(const char*, ...);
void log_log(const char*, ...);
void log_file(const char*, const char*, ...);
void log_debug(const char*, ...);
void log_error(const char*, ...);

#endif /* LOG_H_ */
