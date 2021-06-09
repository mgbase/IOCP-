#ifndef LIBSINGULARITY_H
#define LIBSINGULARITY_H

#if defined (_WIN32)
#ifdef LIBSINGULARITY_EXPORTS
#define LIBSINGULARITY_API __declspec(dllexport)
#else
#define LIBSINGULARITY_API __declspec(dllimport)
#endif
#else
#define LIBSINGULARITY_API
#endif

#endif


