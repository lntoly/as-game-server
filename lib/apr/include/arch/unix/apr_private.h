/* include/arch/unix/apr_private.h.  Generated from apr_private.h.in by configure.  */
/* include/arch/unix/apr_private.h.in.  Generated from configure.in by autoheader.  */


#ifndef APR_PRIVATE_H
#define APR_PRIVATE_H


/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define if apr_allocator should use mmap */
/* #undef APR_ALLOCATOR_USES_MMAP */

/* Define as function which can be used for conversion of strings to
   apr_int64_t */
#define APR_INT64_STRFN _strtoi64

/* Define as function used for conversion of strings to apr_off_t */
#define APR_OFF_T_STRFN _strtoi64

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to path of random device */
#define DEV_RANDOM "/dev/urandom"

/* Define if struct dirent has an inode member */
#define DIRENT_INODE d_ino

/* Define if struct dirent has a d_type member */
/* #undef DIRENT_TYPE */

/* Define if DSO support uses dlfcn.h */
/* #undef DSO_USE_DLFCN */

/* Define if DSO support uses dyld.h */
/* #undef DSO_USE_DYLD */

/* Define if DSO support uses shl_load */
/* #undef DSO_USE_SHL */

/* Define to list of paths to EGD sockets */
/* #undef EGD_DEFAULT_SOCKET */

/* Define if fcntl locks affect threads within the process */
/* #undef FCNTL_IS_GLOBAL */

/* Define if fcntl returns EACCES when F_SETLK is already held */
/* #undef FCNTL_TRYACQUIRE_EACCES */

/* Define if flock locks affect threads within the process */
/* #undef FLOCK_IS_GLOBAL */

/* Define if gethostbyaddr is thread safe */
/* #undef GETHOSTBYADDR_IS_THREAD_SAFE */

/* Define if gethostbyname is thread safe */
/* #undef GETHOSTBYNAME_IS_THREAD_SAFE */

/* Define if gethostbyname_r has the glibc style */
/* #undef GETHOSTBYNAME_R_GLIBC2 */

/* Define if gethostbyname_r has the hostent_data for the third argument */
/* #undef GETHOSTBYNAME_R_HOSTENT_DATA */

/* Define if getservbyname is thread safe */
/* #undef GETSERVBYNAME_IS_THREAD_SAFE */

/* Define if getservbyname_r has the glibc style */
/* #undef GETSERVBYNAME_R_GLIBC2 */

/* Define if getservbyname_r has the OSF/1 style */
/* #undef GETSERVBYNAME_R_OSF1 */

/* Define if getservbyname_r has the Solaris style */
/* #undef GETSERVBYNAME_R_SOLARIS */

/* Define if accept4 function is supported */
/* #undef HAVE_ACCEPT4 */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
/* #undef HAVE_ALLOCA_H */

/* Define to 1 if you have the <arpa/inet.h> header file. */
/* #undef HAVE_ARPA_INET_H */

/* Define if compiler provides atomic builtins */
/* #undef HAVE_ATOMIC_BUILTINS */

/* Define if BONE_VERSION is defined in sys/socket.h */
/* #undef HAVE_BONE_VERSION */

/* Define to 1 if you have the <ByteOrder.h> header file. */
/* #undef HAVE_BYTEORDER_H */

/* Define to 1 if you have the `calloc' function. */
#define HAVE_CALLOC 1

/* Define to 1 if you have the <conio.h> header file. */
#define HAVE_CONIO_H 1

/* Define to 1 if you have the `create_area' function. */
/* #undef HAVE_CREATE_AREA */

/* Define to 1 if you have the `create_sem' function. */
/* #undef HAVE_CREATE_SEM */

/* Define to 1 if you have the <crypt.h> header file. */
/* #undef HAVE_CRYPT_H */

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the declaration of `sys_siglist', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_SIGLIST 0

/* Define to 1 if you have the <dirent.h> header file. */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dir.h> header file. */
#define HAVE_DIR_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have the <dl.h> header file. */
/* #undef HAVE_DL_H */

/* Define if dup3 function is supported */
/* #undef HAVE_DUP3 */

/* Define if EGD is supported */
/* #undef HAVE_EGD */

/* Define if the epoll interface is supported */
/* #undef HAVE_EPOLL */

/* Define if epoll_create1 function is supported */
/* #undef HAVE_EPOLL_CREATE1 */

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `fdatasync' function. */
/* #undef HAVE_FDATASYNC */

/* Define to 1 if you have the `flock' function. */
/* #undef HAVE_FLOCK */

/* Define to 1 if you have the `fork' function. */
/* #undef HAVE_FORK */

/* Define if F_SETLK is defined in fcntl.h */
/* #undef HAVE_F_SETLK */

/* Define if getaddrinfo accepts the AI_ADDRCONFIG flag */
/* #undef HAVE_GAI_ADDRCONFIG */

/* Define to 1 if you have the `gai_strerror' function. */
#define HAVE_GAI_STRERROR 1

/* Define if getaddrinfo exists and works well enough for APR */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getenv' function. */
#define HAVE_GETENV 1

/* Define to 1 if you have the `getgrgid_r' function. */
/* #undef HAVE_GETGRGID_R */

/* Define to 1 if you have the `getgrnam_r' function. */
/* #undef HAVE_GETGRNAM_R */

/* Define to 1 if you have the `gethostbyaddr_r' function. */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define to 1 if you have the `gethostbyname_r' function. */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define to 1 if you have the `getifaddrs' function. */
/* #undef HAVE_GETIFADDRS */

/* Define if getnameinfo exists */
#define HAVE_GETNAMEINFO 1

/* Define to 1 if you have the `getpass' function. */
/* #undef HAVE_GETPASS */

/* Define to 1 if you have the `getpassphrase' function. */
/* #undef HAVE_GETPASSPHRASE */

/* Define to 1 if you have the `getpwnam_r' function. */
/* #undef HAVE_GETPWNAM_R */

/* Define to 1 if you have the `getpwuid_r' function. */
/* #undef HAVE_GETPWUID_R */

/* Define to 1 if you have the `getrlimit' function. */
/* #undef HAVE_GETRLIMIT */

/* Define to 1 if you have the `getservbyname_r' function. */
/* #undef HAVE_GETSERVBYNAME_R */

/* Define to 1 if you have the `gmtime_r' function. */
/* #undef HAVE_GMTIME_R */

/* Define to 1 if you have the <grp.h> header file. */
/* #undef HAVE_GRP_H */

/* Define if hstrerror is present */
/* #undef HAVE_HSTRERROR */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <io.h> header file. */
#define HAVE_IO_H 1

/* Define to 1 if you have the `isinf' function. */
/* #undef HAVE_ISINF */

/* Define to 1 if you have the `isnan' function. */
#define HAVE_ISNAN 1

/* Define to 1 if you have the <kernel/OS.h> header file. */
/* #undef HAVE_KERNEL_OS_H */

/* Define to 1 if you have the `kqueue' function. */
/* #undef HAVE_KQUEUE */

/* Define to 1 if you have the <langinfo.h> header file. */
/* #undef HAVE_LANGINFO_H */

/* Define to 1 if you have the `bsd' library (-lbsd). */
/* #undef HAVE_LIBBSD */

/* Define to 1 if you have the `sendfile' library (-lsendfile). */
/* #undef HAVE_LIBSENDFILE */

/* Define to 1 if you have the `truerand' library (-ltruerand). */
/* #undef HAVE_LIBTRUERAND */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `localtime_r' function. */
/* #undef HAVE_LOCALTIME_R */

/* Define if LOCK_EX is defined in sys/file.h */
/* #undef HAVE_LOCK_EX */

/* Define to 1 if you have the <mach-o/dyld.h> header file. */
/* #undef HAVE_MACH_O_DYLD_H */

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define if MAP_ANON is defined in sys/mman.h */
/* #undef HAVE_MAP_ANON */

/* Define to 1 if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mkstemp' function. */
/* #undef HAVE_MKSTEMP */

/* Define to 1 if you have the `mkstemp64' function. */
/* #undef HAVE_MKSTEMP64 */

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `mmap64' function. */
/* #undef HAVE_MMAP64 */

/* Define to 1 if you have the `munmap' function. */
/* #undef HAVE_MUNMAP */

/* Define to 1 if you have the <netdb.h> header file. */
/* #undef HAVE_NETDB_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
/* #undef HAVE_NETINET_IN_H */

/* Define to 1 if you have the <netinet/sctp.h> header file. */
/* #undef HAVE_NETINET_SCTP_H */

/* Define to 1 if you have the <netinet/sctp_uio.h> header file. */
/* #undef HAVE_NETINET_SCTP_UIO_H */

/* Defined if netinet/tcp.h is present */
/* #undef HAVE_NETINET_TCP_H */

/* Define to 1 if you have the <net/errno.h> header file. */
/* #undef HAVE_NET_ERRNO_H */

/* Define to 1 if you have the `nl_langinfo' function. */
/* #undef HAVE_NL_LANGINFO */

/* Define to 1 if you have the <os2.h> header file. */
/* #undef HAVE_OS2_H */

/* Define to 1 if you have the <osreldate.h> header file. */
/* #undef HAVE_OSRELDATE_H */

/* Define to 1 if you have the <OS.h> header file. */
/* #undef HAVE_OS_H */

/* Define to 1 if you have the `poll' function. */
/* #undef HAVE_POLL */

/* Define if POLLIN is defined */
/* #undef HAVE_POLLIN */

/* Define to 1 if you have the <poll.h> header file. */
/* #undef HAVE_POLL_H */

/* Define to 1 if you have the `port_create' function. */
/* #undef HAVE_PORT_CREATE */

/* Define to 1 if you have the <process.h> header file. */
#define HAVE_PROCESS_H 1

/* Define to 1 if you have the `pthread_attr_setguardsize' function. */
/* #undef HAVE_PTHREAD_ATTR_SETGUARDSIZE */

/* Define to 1 if you have the <pthread.h> header file. */
/* #undef HAVE_PTHREAD_H */

/* Define to 1 if you have the `pthread_key_delete' function. */
/* #undef HAVE_PTHREAD_KEY_DELETE */

/* Define to 1 if you have the `pthread_mutexattr_setpshared' function. */
/* #undef HAVE_PTHREAD_MUTEXATTR_SETPSHARED */

/* Define if recursive pthread mutexes are available */
/* #undef HAVE_PTHREAD_MUTEX_RECURSIVE */

/* Define if cross-process robust mutexes are available */
/* #undef HAVE_PTHREAD_MUTEX_ROBUST */

/* Define if PTHREAD_PROCESS_SHARED is defined in pthread.h */
/* #undef HAVE_PTHREAD_PROCESS_SHARED */

/* Define if pthread rwlocks are available */
/* #undef HAVE_PTHREAD_RWLOCKS */

/* Define to 1 if you have the `pthread_rwlock_init' function. */
/* #undef HAVE_PTHREAD_RWLOCK_INIT */

/* Define to 1 if you have the `pthread_yield' function. */
/* #undef HAVE_PTHREAD_YIELD */

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the <pwd.h> header file. */
/* #undef HAVE_PWD_H */

/* Define to 1 if you have the `readdir64_r' function. */
/* #undef HAVE_READDIR64_R */

/* Define to 1 if you have the <sched.h> header file. */
/* #undef HAVE_SCHED_H */

/* Define to 1 if you have the `sched_yield' function. */
/* #undef HAVE_SCHED_YIELD */

/* Define to 1 if you have the <semaphore.h> header file. */
#define HAVE_SEMAPHORE_H 1

/* Define to 1 if you have the `semctl' function. */
/* #undef HAVE_SEMCTL */

/* Define to 1 if you have the `semget' function. */
/* #undef HAVE_SEMGET */

/* Define to 1 if you have the `sem_close' function. */
/* #undef HAVE_SEM_CLOSE */

/* Define to 1 if you have the `sem_post' function. */
/* #undef HAVE_SEM_POST */

/* Define if SEM_UNDO is defined in sys/sem.h */
/* #undef HAVE_SEM_UNDO */

/* Define to 1 if you have the `sem_unlink' function. */
/* #undef HAVE_SEM_UNLINK */

/* Define to 1 if you have the `sem_wait' function. */
/* #undef HAVE_SEM_WAIT */

/* Define to 1 if you have the `sendfile' function. */
#define HAVE_SENDFILE 1

/* Define to 1 if you have the `sendfile64' function. */
/* #undef HAVE_SENDFILE64 */

/* Define to 1 if you have the `sendfilev' function. */
/* #undef HAVE_SENDFILEV */

/* Define to 1 if you have the `sendfilev64' function. */
/* #undef HAVE_SENDFILEV64 */

/* Define to 1 if you have the `send_file' function. */
/* #undef HAVE_SEND_FILE */

/* Define to 1 if you have the `setenv' function. */
/* #undef HAVE_SETENV */

/* Define to 1 if you have the `setrlimit' function. */
/* #undef HAVE_SETRLIMIT */

/* Define to 1 if you have the `setsid' function. */
/* #undef HAVE_SETSID */

/* Define to 1 if you have the `set_h_errno' function. */
/* #undef HAVE_SET_H_ERRNO */

/* Define to 1 if you have the `shmat' function. */
/* #undef HAVE_SHMAT */

/* Define to 1 if you have the `shmctl' function. */
/* #undef HAVE_SHMCTL */

/* Define to 1 if you have the `shmdt' function. */
/* #undef HAVE_SHMDT */

/* Define to 1 if you have the `shmget' function. */
/* #undef HAVE_SHMGET */

/* Define to 1 if you have the `shm_open' function. */
/* #undef HAVE_SHM_OPEN */

/* Define to 1 if you have the `shm_unlink' function. */
/* #undef HAVE_SHM_UNLINK */

/* Define to 1 if you have the `sigaction' function. */
/* #undef HAVE_SIGACTION */

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the `sigsuspend' function. */
/* #undef HAVE_SIGSUSPEND */

/* Define to 1 if you have the `sigwait' function. */
/* #undef HAVE_SIGWAIT */

/* Whether you have socklen_t */
/* #undef HAVE_SOCKLEN_T */

/* Define if the SOCK_CLOEXEC flag is supported */
/* #undef HAVE_SOCK_CLOEXEC */

/* Define if SO_ACCEPTFILTER is defined in sys/socket.h */
/* #undef HAVE_SO_ACCEPTFILTER */

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror_r' function. */
/* #undef HAVE_STRERROR_R */

/* Define to 1 if you have the `stricmp' function. */
#define HAVE_STRICMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strnicmp' function. */
#define HAVE_STRNICMP 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define if struct impreq was found */
/* #undef HAVE_STRUCT_IPMREQ */

/* Define to 1 if `st_atimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIMENSEC */

/* Define to 1 if `st_atime_n' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIME_N */

/* Define to 1 if `st_atim.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC */

/* Define to 1 if `st_blocks' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BLOCKS */

/* Define to 1 if `st_ctimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_CTIMENSEC */

/* Define to 1 if `st_ctime_n' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_CTIME_N */

/* Define to 1 if `st_ctim.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_CTIM_TV_NSEC */

/* Define to 1 if `st_mtimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIMENSEC */

/* Define to 1 if `st_mtime_n' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIME_N */

/* Define to 1 if `st_mtim.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC */

/* Define to 1 if `tm_gmtoff' is a member of `struct tm'. */
/* #undef HAVE_STRUCT_TM_TM_GMTOFF */

/* Define to 1 if `__tm_gmtoff' is a member of `struct tm'. */
/* #undef HAVE_STRUCT_TM___TM_GMTOFF */

/* Define to 1 if you have the <sysapi.h> header file. */
/* #undef HAVE_SYSAPI_H */

/* Define to 1 if you have the <sysgtime.h> header file. */
/* #undef HAVE_SYSGTIME_H */

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
/* #undef HAVE_SYS_IOCTL_H */

/* Define to 1 if you have the <sys/ipc.h> header file. */
/* #undef HAVE_SYS_IPC_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
/* #undef HAVE_SYS_MMAN_H */

/* Define to 1 if you have the <sys/mutex.h> header file. */
/* #undef HAVE_SYS_MUTEX_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/poll.h> header file. */
/* #undef HAVE_SYS_POLL_H */

/* Define to 1 if you have the <sys/resource.h> header file. */
/* #undef HAVE_SYS_RESOURCE_H */

/* Define to 1 if you have the <sys/select.h> header file. */
/* #undef HAVE_SYS_SELECT_H */

/* Define to 1 if you have the <sys/sem.h> header file. */
/* #undef HAVE_SYS_SEM_H */

/* Define to 1 if you have the <sys/sendfile.h> header file. */
/* #undef HAVE_SYS_SENDFILE_H */

/* Define to 1 if you have the <sys/shm.h> header file. */
/* #undef HAVE_SYS_SHM_H */

/* Define to 1 if you have the <sys/signal.h> header file. */
/* #undef HAVE_SYS_SIGNAL_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
/* #undef HAVE_SYS_SOCKET_H */

/* Define to 1 if you have the <sys/sockio.h> header file. */
/* #undef HAVE_SYS_SOCKIO_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/sysctl.h> header file. */
/* #undef HAVE_SYS_SYSCTL_H */

/* Define to 1 if you have the <sys/syslimits.h> header file. */
/* #undef HAVE_SYS_SYSLIMITS_H */

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
/* #undef HAVE_SYS_UIO_H */

/* Define to 1 if you have the <sys/un.h> header file. */
/* #undef HAVE_SYS_UN_H */

/* Define to 1 if you have the <sys/uuid.h> header file. */
/* #undef HAVE_SYS_UUID_H */

/* Define to 1 if you have the <sys/wait.h> header file. */
/* #undef HAVE_SYS_WAIT_H */

/* Define if TCP_CORK is defined in netinet/tcp.h */
/* #undef HAVE_TCP_CORK */

/* Define if TCP_NODELAY and TCP_CORK can be enabled at the same time */
/* #undef HAVE_TCP_NODELAY_WITH_CORK */

/* Define if TCP_NOPUSH is defined in netinet/tcp.h */
/* #undef HAVE_TCP_NOPUSH */

/* Define to 1 if you have the <termios.h> header file. */
/* #undef HAVE_TERMIOS_H */

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the <tpfeq.h> header file. */
/* #undef HAVE_TPFEQ_H */

/* Define to 1 if you have the <tpfio.h> header file. */
/* #undef HAVE_TPFIO_H */

/* Define if truerand is supported */
/* #undef HAVE_TRUERAND */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <unix.h> header file. */
/* #undef HAVE_UNIX_H */

/* Define to 1 if you have the `unsetenv' function. */
/* #undef HAVE_UNSETENV */

/* Define to 1 if you have the `utime' function. */
#define HAVE_UTIME 1

/* Define to 1 if you have the `utimes' function. */
/* #undef HAVE_UTIMES */

/* Define to 1 if you have the `uuid_create' function. */
/* #undef HAVE_UUID_CREATE */

/* Define to 1 if you have the `uuid_generate' function. */
/* #undef HAVE_UUID_GENERATE */

/* Define to 1 if you have the <uuid.h> header file. */
/* #undef HAVE_UUID_H */

/* Define to 1 if you have the <uuid/uuid.h> header file. */
/* #undef HAVE_UUID_UUID_H */

/* Define if C compiler supports VLA */
#define HAVE_VLA 1

/* Define to 1 if you have the `waitpid' function. */
/* #undef HAVE_WAITPID */

/* Define to 1 if you have the <windows.h> header file. */
#define HAVE_WINDOWS_H 1

/* Define to 1 if you have the <winsock2.h> header file. */
#define HAVE_WINSOCK2_H 1

/* Define to 1 if you have the `writev' function. */
/* #undef HAVE_WRITEV */

/* Define for z/OS pthread API nuances */
/* #undef HAVE_ZOS_PTHREADS */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define if EAI_ error codes from getaddrinfo are negative */
/* #undef NEGATIVE_EAI */

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define if POSIX semaphores affect threads within the process */
/* #undef POSIXSEM_IS_GLOBAL */

/* Define on PowerPC 405 where errata 77 applies */
/* #undef PPC405_ERRATA */

/* Define if pthread_attr_getdetachstate() has one arg */
/* #undef PTHREAD_ATTR_GETDETACHSTATE_TAKES_ONE_ARG */

/* Define if pthread_getspecific() has two args */
/* #undef PTHREAD_GETSPECIFIC_TAKES_TWO_ARGS */

/* Define if readdir is thread safe */
/* #undef READDIR_IS_THREAD_SAFE */

/* Define to 1 if the `setpgrp' function takes no argument. */
/* #undef SETPGRP_VOID */

/* */
/* #undef SIGWAIT_TAKES_ONE_ARG */

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of ino_t */
/* #undef SIZEOF_INO_T */

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of off_t */
#define SIZEOF_OFF_T 4

/* The size of pid_t */
#define SIZEOF_PID_T 4

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of size_t */
#define SIZEOF_SIZE_T 4

/* The size of ssize_t */
#define SIZEOF_SSIZE_T 4

/* The size of struct iovec */
#define SIZEOF_STRUCT_IOVEC 0

/* The size of `void*', as computed by sizeof. */
#define SIZEOF_VOIDP 4

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if strerror returns int */
/* #undef STRERROR_R_RC_INT */

/* Define if SysV semaphores affect threads within the process */
/* #undef SYSVSEM_IS_GLOBAL */

/* Define if use of generic atomics is requested */
#define USE_ATOMICS_GENERIC 1

/* Define if BeOS Semaphores will be used */
/* #undef USE_BEOSSEM */

/* Define if SVR4-style fcntl() will be used */
/* #undef USE_FCNTL_SERIALIZE */

/* Define if 4.2BSD-style flock() will be used */
/* #undef USE_FLOCK_SERIALIZE */

/* Define if BeOS areas will be used */
/* #undef USE_SHMEM_BEOS */

/* Define if BeOS areas will be used */
/* #undef USE_SHMEM_BEOS_ANON */

/* Define if 4.4BSD-style mmap() via MAP_ANON will be used */
/* #undef USE_SHMEM_MMAP_ANON */

/* Define if mmap() via POSIX.1 shm_open() on temporary file will be used */
/* #undef USE_SHMEM_MMAP_SHM */

/* Define if Classical mmap() on temporary file will be used */
/* #undef USE_SHMEM_MMAP_TMP */

/* Define if SVR4-style mmap() on /dev/zero will be used */
/* #undef USE_SHMEM_MMAP_ZERO */

/* Define if OS/2 DosAllocSharedMem() will be used */
/* #undef USE_SHMEM_OS2 */

/* Define if OS/2 DosAllocSharedMem() will be used */
/* #undef USE_SHMEM_OS2_ANON */

/* Define if SysV IPC shmget() will be used */
/* #undef USE_SHMEM_SHMGET */

/* Define if SysV IPC shmget() will be used */
/* #undef USE_SHMEM_SHMGET_ANON */

/* Define if Windows shared memory will be used */
#define USE_SHMEM_WIN32 1

/* Define if Windows CreateFileMapping() will be used */
#define USE_SHMEM_WIN32_ANON 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define if SysV IPC semget() will be used */
/* #undef USE_SYSVSEM_SERIALIZE */

/* Define if apr_wait_for_io_or_timeout() uses poll(2) */
/* #undef WAITIO_USES_POLL */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
#define gid_t int

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> doesn't define. */
#define uid_t int


/* switch this on if we have a BeOS version below BONE */
#if BEOS && !HAVE_BONE_VERSION
#define BEOS_R5 1
#else
#define BEOS_BONE 1
#endif

/*
 * Darwin 10's default compiler (gcc42) builds for both 64 and
 * 32 bit architectures unless specifically told not to.
 * In those cases, we need to override types depending on how
 * we're being built at compile time.
 * NOTE: This is an ugly work-around for Darwin's
 * concept of universal binaries, a single package
 * (executable, lib, etc...) which contains both 32
 * and 64 bit versions. The issue is that if APR is
 * built universally, if something else is compiled
 * against it, some bit sizes will depend on whether
 * it is 32 or 64 bit. This is determined by the __LP64__
 * flag. Since we need to support both, we have to
 * handle OS X unqiuely.
 */
#ifdef DARWIN_10

#define APR_OFF_T_STRFN _strtoi64
#define APR_INT64_STRFN _strtoi64
#define SIZEOF_LONG 4
#define SIZEOF_SIZE_T 4
#define SIZEOF_SSIZE_T 4
#define SIZEOF_VOIDP 4
#define SIZEOF_STRUCT_IOVEC 0

#ifdef __LP64__
 #define APR_INT64_STRFN _strtoi64
 #define SIZEOF_LONG 4
 #define SIZEOF_SIZE_T 4
 #define SIZEOF_SSIZE_T 4
 #define SIZEOF_VOIDP 4
 #define SIZEOF_STRUCT_IOVEC 0
#else
 #define APR_INT64_STRFN _strtoi64
 #define SIZEOF_LONG 4
 #define SIZEOF_SIZE_T 4
 #define SIZEOF_SSIZE_T 4
 #define SIZEOF_VOIDP 4
 #define SIZEOF_STRUCT_IOVEC 0
#endif

#define APR_OFF_T_STRFN _strtoi64
#define APR_OFF_T_STRFN _strtoi64
 

/* #undef SETPGRP_VOID */
#ifdef __DARWIN_UNIX03
 #define SETPGRP_VOID 1
#else
/* #undef SETPGRP_VOID */
#endif
 
#endif /* DARWIN_10 */

/*
 * Include common private declarations.
 */
#include "../apr_private_common.h"
#endif /* APR_PRIVATE_H */

