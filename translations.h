#ifndef _TRANSLATIONS_H_
#define _TRANSLATIONS_H_

#ifdef LOCALIZE

// MingW flips out if you don't define this before you try to statically link libintl.
// This should prevent 'undefined reference to `_imp__libintl_gettext`' errors.
#if defined _WIN32 || defined __CYGWIN__
 #ifndef LIBINTL_STATIC
  #define LIBINTL_STATIC
 #endif
#endif

#include <cstdio>
#include <libintl.h>
#include <clocale>
#include <string>
#define _(STRING) gettext(STRING)
inline const char * pgettext(const char *context, const char *msgid)
{
    // need to construct the string manually,
    // to correctly handle strings loaded from json.
    // could probably do this more efficiently without using std::string.
    std::string context_id(context);
    context_id += '\004';
    context_id += msgid;
    // null domain, uses global translation domain
    const char *msg_ctxt_id = context_id.c_str();
    const char *translation = dcgettext(NULL, msg_ctxt_id, LC_MESSAGES);
    if (translation == msg_ctxt_id) {
        return msgid;
    } else {
        return translation;
    }
}

#else // !LOCALIZE

#define _(STRING) STRING
#define ngettext(STRING1, STRING2, COUNT) (COUNT < 2 ? STRING1 : STRING2)
#define pgettext(STRING1, STRING2) STRING2

#endif // LOCALIZE

#endif // _TRANSLATIONS_H_
