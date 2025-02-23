#
# Copyright (c) 2010-2015, 2017 Todd C. Miller <Todd.Miller@courtesan.com>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# doc/Makefile.  Generated from Makefile.in by configure.
#

#### Start of system configuration section. ####

srcdir = .
docdir = $(datarootdir)/doc/$(PACKAGE_TARNAME)
top_builddir = ..
top_srcdir = ..

# Tools to use
SED = /bin/sed
MANDOC = mandoc
MANCOMPRESS = 
MANCOMPRESSEXT = 
TR = /usr/bin/tr

# Our install program supports extra flags...
INSTALL = $(SHELL) $(top_srcdir)/install-sh -c
INSTALL_OWNER = -o $(install_uid) -g $(install_gid)

# Where to install things...
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
sbindir = $(exec_prefix)/sbin
sysconfdir = /etc
libexecdir = $(exec_prefix)/libexec
datarootdir = $(prefix)/share
localstatedir = $(prefix)/var
mandir = $(prefix)/man

# Directory to copy man pages from
mansrcdir = .

# Directory in which to install the man page
mantype = mdoc
mansectsu = 8
mansectform = 5
mandirsu = $(mandir)/man$(mansectsu)
mandirform = $(mandir)/man$(mansectform)

# User and group ids the installed files should be "owned" by
install_uid = 0
install_gid = 0

# Set to non-empty for development mode
DEVEL = 

#### End of system configuration section. ####

SHELL = /bin/bash

DOCS =	$(mansrcdir)/sudo.$(mantype) $(mansrcdir)/visudo.$(mantype) \
	$(mansrcdir)/sudo.conf.$(mantype) $(mansrcdir)/sudoers.$(mantype) \
	$(mansrcdir)/sudoers.ldap.$(mantype) $(mansrcdir)/sudoers.$(mantype) \
	$(mansrcdir)/sudoreplay.$(mantype) $(mansrcdir)/sudo_plugin.$(mantype)

DEVDOCS = $(srcdir)/sudo.man.in $(srcdir)/sudo.cat \
	  $(srcdir)/visudo.man.in $(srcdir)/visudo.cat \
	  $(srcdir)/sudo.conf.man.in $(srcdir)/sudo.conf.cat \
	  $(srcdir)/sudoers.man.in $(srcdir)/sudoers.cat \
	  $(srcdir)/sudoers.ldap.man.in $(srcdir)/sudoers.ldap.cat \
	  $(srcdir)/sudoers.man.in $(srcdir)/sudoers.cat \
	  $(srcdir)/sudoreplay.man.in $(srcdir)/sudoreplay.cat \
	  $(srcdir)/sudo_plugin.man.in $(srcdir)/sudo_plugin.cat

OTHER_DOCS = $(top_srcdir)/ChangeLog $(top_srcdir)/README \
	     $(top_srcdir)/NEWS $(srcdir)/HISTORY $(srcdir)/CONTRIBUTORS \
	     $(srcdir)/LICENSE $(srcdir)/TROUBLESHOOTING $(srcdir)/UPGRADE

OTHER_DOCS_LDAP = $(top_srcdir)/README.LDAP $(srcdir)/schema.*

VERSION = 1.8.21
PACKAGE_TARNAME = sudo

all: $(DEVDOCS) $(DOCS)

lint: all
	@if [ "$(mantype)" != "mdoc" ]; then \
	    echo "make lint only supported for mdoc manuals" 1>&2; \
	    exit 1; \
	else \
	    for m in $(DOCS); do \
		echo $(MANDOC) -Tlint $$m; \
		$(MANDOC) -Tlint $$m; \
	    done; \
	fi

Makefile: $(srcdir)/Makefile.in
	cd $(top_builddir) && ./config.status --file doc/Makefile

.SUFFIXES: .man

varsub: $(top_srcdir)/configure.ac
	@if [ -n "$(DEVEL)" ]; then \
	    printf 's#@%s@#1#\ns#@%s@#1#\ns#@%s@#1#\ns#@%s@#1#\ns#@%s@#/etc#g\ns#@%s@#/usr/local#g\ns#@%s@#5#g\ns#@%s@#8#g\ns#@%s@#%s#\n' SEMAN BAMAN LCMAN PSMAN sysconfdir prefix mansectform mansectsu PACKAGE_VERSION $(VERSION) > $@; \
	    $(SED) -n '/Begin initial values for man page substitution/,/End initial values for man page substitution/{;p;}' $(top_srcdir)/configure.ac | $(SED) -e '/^#/d' -e 's/^/s#@/' -e 's/=[\\"]*/@#/' -e 's/[\\"]*$$/#g/' >> $@; \
	fi

$(srcdir)/sudo.man.in: $(srcdir)/sudo.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM sudo.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/sudo.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/sudo.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "SUDO" \)"8"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

sudo.man.sed: $(srcdir)/fixman.sh
	BAMAN=0 LCMAN=0 SEMAN=0 PSMAN=0 $(SHELL) $(srcdir)/fixman.sh $@

$(mansrcdir)/sudo.man: $(top_builddir)/config.status $(srcdir)/sudo.man.in sudo.man.sed
	(cd $(top_builddir) && $(SHELL) config.status --file=-) < $(srcdir)/sudo.man.in | $(SED) -f $@.sed > $@

sudo.mdoc.sed: $(srcdir)/fixmdoc.sh
	BAMAN=0 LCMAN=0 SEMAN=0 PSMAN=0 $(SHELL) $(srcdir)/fixmdoc.sh $@

$(mansrcdir)/sudo.mdoc: $(top_builddir)/config.status $(srcdir)/sudo.mdoc.in sudo.mdoc.sed
	(cd $(top_builddir) && $(SHELL) config.status --file=-) < $(srcdir)/sudo.mdoc.in | $(SED) -f $@.sed > $@

$(srcdir)/sudo.cat: varsub $(srcdir)/sudo.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/sudo.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

$(srcdir)/visudo.man.in: $(srcdir)/visudo.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM visudo.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/visudo.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/visudo.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "VISUDO" \)"8"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

$(mansrcdir)/visudo.man: $(top_builddir)/config.status $(srcdir)/visudo.man.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(mansrcdir)/visudo.mdoc: $(top_builddir)/config.status $(srcdir)/visudo.mdoc.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(srcdir)/visudo.cat: varsub $(srcdir)/visudo.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/visudo.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

$(srcdir)/sudo.conf.man.in: $(srcdir)/sudo.conf.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM sudo.conf.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/sudo.conf.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/sudo.conf.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "VISUDO" \)"8"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

$(mansrcdir)/sudo.conf.man: $(top_builddir)/config.status $(srcdir)/sudo.conf.man.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(mansrcdir)/sudo.conf.mdoc: $(top_builddir)/config.status $(srcdir)/sudo.conf.mdoc.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(srcdir)/sudo.conf.cat: varsub $(srcdir)/sudo.conf.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/sudo.conf.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

$(srcdir)/sudoers.man.in: $(srcdir)/sudoers.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM sudoers.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/sudoers.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/sudoers.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "SUDOERS" \)"5"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

sudoers.man.sed: $(srcdir)/fixman.sh
	LCMAN=0 SEMAN=0 PSMAN=0 $(SHELL) $(srcdir)/fixman.sh $@

$(mansrcdir)/sudoers.man: $(top_builddir)/config.status $(srcdir)/sudoers.man.in sudoers.man.sed
	(cd $(top_builddir) && $(SHELL) config.status --file=-) < $(srcdir)/sudoers.man.in | $(SED) -f $@.sed > $@

sudoers.mdoc.sed: $(srcdir)/fixmdoc.sh
	LCMAN=0 SEMAN=0 PSMAN=0 $(SHELL) $(srcdir)/fixmdoc.sh $@

$(mansrcdir)/sudoers.mdoc: $(top_builddir)/config.status $(srcdir)/sudoers.mdoc.in sudoers.mdoc.sed
	(cd $(top_builddir) && $(SHELL) config.status --file=-) < $(srcdir)/sudoers.mdoc.in | $(SED) -f $@.sed > $@

$(srcdir)/sudoers.cat: varsub $(srcdir)/sudoers.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/sudoers.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

$(srcdir)/sudoers.ldap.man.in: $(srcdir)/sudoers.ldap.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM sudoers.ldap.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/sudoers.ldap.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/sudoers.ldap.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "SUDOERS.LDAP" \)"5"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

$(mansrcdir)/sudoers.ldap.man: $(top_builddir)/config.status $(srcdir)/sudoers.ldap.man.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(mansrcdir)/sudoers.ldap.mdoc: $(top_builddir)/config.status $(srcdir)/sudoers.ldap.mdoc.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(srcdir)/sudoers.ldap.cat: varsub $(srcdir)/sudoers.ldap.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/sudoers.ldap.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

$(srcdir)/sudoreplay.man.in: $(srcdir)/sudoreplay.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM sudoreplay.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/sudoreplay.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/sudoreplay.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "SUDOREPLAY" \)"8"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

$(mansrcdir)/sudoreplay.man: $(top_builddir)/config.status $(srcdir)/sudoreplay.man.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(mansrcdir)/sudoreplay.mdoc: $(top_builddir)/config.status $(srcdir)/sudoreplay.mdoc.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(srcdir)/sudoreplay.cat: varsub $(srcdir)/sudoreplay.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/sudoreplay.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

$(srcdir)/sudo_plugin.man.in: $(srcdir)/sudo_plugin.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    mansectsu=`echo @MANSECTSU@|$(TR) A-Z a-z`; \
	    mansectform=`echo @MANSECTFORM@|$(TR) A-Z a-z`; \
	    printf '.\\" DO NOT EDIT THIS FILE, IT IS NOT THE MASTER!\n' > $@; \
	    printf '.\\" IT IS GENERATED AUTOMATICALLY FROM sudo_plugin.mdoc.in\n' >> $@; \
	    $(SED) -n -e '/^.Dd/q' -e '/^\.\\/p' $(srcdir)/sudo_plugin.mdoc.in >> $@; \
	    $(SED) -e "s/$$mansectsu/8/g" -e "s/$$mansectform/5/g" $(srcdir)/sudo_plugin.mdoc.in | $(MANDOC) -Tman | $(SED) -e 's/^\(\.TH "SUDO_PLUGIN" \)"8"\(.*"\)OpenBSD \(.*\)/\1"'$$mansectsu'"\2\3/' -e "s/(5)/($$mansectform)/g" -e "s/(8)/($$mansectsu)/g" >> $@; \
	fi

$(mansrcdir)/sudo_plugin.man: $(top_builddir)/config.status $(srcdir)/sudo_plugin.man.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(mansrcdir)/sudo_plugin.mdoc: $(top_builddir)/config.status $(srcdir)/sudo_plugin.mdoc.in
	cd $(top_builddir) && $(SHELL) config.status --file=doc/$@

$(srcdir)/sudo_plugin.cat: varsub $(srcdir)/sudo_plugin.mdoc.in
	@if [ -n "$(DEVEL)" ]; then \
	    echo "Generating $@"; \
	    $(SED) -f varsub $(srcdir)/sudo_plugin.mdoc.in | $(MANDOC) -Tascii -mdoc | $(SED) -e 's/ OpenBSD \([^ ].*  \)/     \1    /' -e 's/(5)/(4)/g' -e 's/(8)/(1m)/g' > $@; \
	fi

pre-install:

install: install-doc

install-dirs:
	$(SHELL) $(top_srcdir)/mkinstalldirs $(DESTDIR)$(docdir) \
	    $(DESTDIR)$(mandirsu) $(DESTDIR)$(mandirform)

install-binaries:

install-includes:

install-doc: install-dirs
	for f in $(OTHER_DOCS); do $(INSTALL) $(INSTALL_OWNER) -m 0644 $$f $(DESTDIR)$(docdir); done
	#for f in $(OTHER_DOCS_LDAP); do $(INSTALL) $(INSTALL_OWNER) -m 0644 $$f $(DESTDIR)$(docdir); done
	$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/sudo.$(mantype) $(DESTDIR)$(mandirsu)/sudo.$(mansectsu)
	$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/sudo_plugin.$(mantype) $(DESTDIR)$(mandirsu)/sudo_plugin.$(mansectsu)
	$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/sudoreplay.$(mantype) $(DESTDIR)$(mandirsu)/sudoreplay.$(mansectsu)
	$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/visudo.$(mantype) $(DESTDIR)$(mandirsu)/visudo.$(mansectsu)
	$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/sudo.conf.$(mantype) $(DESTDIR)$(mandirform)/sudo.conf.$(mansectform)
	$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/sudoers.$(mantype) $(DESTDIR)$(mandirform)/sudoers.$(mansectform)
	#$(INSTALL) $(INSTALL_OWNER) -m 0644 $(mansrcdir)/sudoers.ldap.$(mantype) $(DESTDIR)$(mandirform)/sudoers.ldap.$(mansectform)
	@if test -n "$(MANCOMPRESS)"; then \
	    for f in $(mandirsu)/sudo.$(mansectsu) $(mandirsu)/sudo_plugin.$(mansectsu) $(mandirsu)/sudoreplay.$(mansectsu) $(mandirsu)/visudo.$(mansectsu) $(mandirform)/sudo.conf.$(mansectform) $(mandirform)/sudoers.$(mansectform) $(mandirform)/sudoers.ldap.$(mansectform); do \
		if test -f $(DESTDIR)$$f; then \
		    echo $(MANCOMPRESS) -f $(DESTDIR)$$f; \
		    $(MANCOMPRESS) -f $(DESTDIR)$$f; \
		fi; \
	    done; \
	    rm -f $(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu)$(MANCOMPRESSEXT); \
	    echo ln -s sudo.$(mansectsu)$(MANCOMPRESSEXT) $(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu)$(MANCOMPRESSEXT); \
	    ln -s sudo.$(mansectsu)$(MANCOMPRESSEXT) $(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu)$(MANCOMPRESSEXT); \
	else \
	    rm -f $(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu); \
	    echo ln -s sudo.$(mansectsu) $(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu); \
	    ln -s sudo.$(mansectsu) $(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu); \
	fi

install-plugin:

uninstall:
	-rm -rf	$(DESTDIR)$(docdir)
	-rm -f	$(DESTDIR)$(mandirsu)/sudo.$(mansectsu) \
		$(DESTDIR)$(mandirsu)/sudoedit.$(mansectsu) \
		$(DESTDIR)$(mandirsu)/sudo_plugin.$(mansectsu) \
		$(DESTDIR)$(mandirsu)/sudoreplay.$(mansectsu) \
		$(DESTDIR)$(mandirsu)/visudo.$(mansectsu) \
		$(DESTDIR)$(mandirform)/sudo.conf.$(mansectform) \
		$(DESTDIR)$(mandirform)/sudoers.$(mansectform) \
		$(DESTDIR)$(mandirform)/sudoers.ldap.$(mansectform)

splint:

cppcheck:

check:

clean:
	-rm -f varsub *.sed

mostlyclean: clean

distclean: clean
	-rm -rf Makefile config.log *.man *.mdoc

clobber: distclean

realclean: distclean

cleandir: distclean
