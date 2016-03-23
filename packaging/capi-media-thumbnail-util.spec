Name:       capi-media-thumbnail-util
Summary:    A media thumbnail util library in Tizen Native API
Version: 0.1.3
Release:    1
Group:      Multimedia/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(libmedia-utils)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(media-thumbnail)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
A media thumbnail util library in Tizen Native API.

%package devel
Summary:  A media thumbnail util library in Tizen Native API (Development)
Group:    Multimedia/Development
Requires: %{name} = %{version}-%{release}

%description devel
A media thumbnail util library in Tizen Native API. (Development files included)

%prep
%setup -q


%build
export CFLAGS+=" -Wextra -Wno-array-bounds"
export CFLAGS+=" -Wno-ignored-qualifiers -Wno-unused-parameter -Wshadow"
export CFLAGS+=" -Wwrite-strings -Wswitch-default"
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
make %{?jobs:-j%jobs}

%install
%make_install
mkdir -p %{buildroot}/%{_datadir}/license
cp -rf %{_builddir}/%{name}-%{version}/LICENSE.APLv2.0 %{buildroot}/%{_datadir}/license/%{name}
%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-media-thumbnail-util.manifest
%{_libdir}/libcapi-media-thumbnail-util.so
%{_datadir}/license/%{name}

%files devel
%{_includedir}/media/*.h
%{_libdir}/pkgconfig/capi-media-thumbnail-util.pc
