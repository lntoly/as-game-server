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
void log_file_with_time(const char*, const char*, ...);

#define log_debug(fmt, arg...) \
		do { \
			log_print(fmt, ##arg); \
			log_file_with_time("log/debug.log", fmt, ##arg); \
		} while (0)

#endif /* LOG_H_ */
