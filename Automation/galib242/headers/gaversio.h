/* ----------------------------------------------------------------------------
  version.h
  mbwall 30sep94

 DESCRIPTION: -----------------------------------------------------------------
   This is the header file to keep track of the versions and revisions of the
GA library.  Normally this file will remain unchanged, so its RCS status won't
change.  When you're ready to do a major revision or release a new version,
simply touch this file then check everything back in.  The RCS info we keep
here includes the log, so you can document the changes automatically too.  Be 
sure to make a log entry when you do the check in!
   This file is not actually included by any sources.  It is written so that it
could be included (so that you can use the ident command to extract the rcsid
from an object file or library if you needed to), but we don't include it so 
that we don't get those annoying "rcsid not used" warnings during compilation.

---------------------------------------------------------------------------- */
#ifndef _version_h_
#define _version_h_

static char *rcsid = "$Header: /usr/people/mbwall/src/galib/ga/RCS/gaversio.h,v 1.1 1996/11/13 01:36:31 mbwall Exp mbwall $";

#endif
