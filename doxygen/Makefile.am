AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = compta.dox compta.page txt_common fig_common

DISTCLEANFILES  = compta.dox
DISTCLEANFILES += Makefile

dist-hook:
	rm -rf `find $(distdir)/ -name .svn`
	rm -rf `find $(distdir)/ -name .deps`

