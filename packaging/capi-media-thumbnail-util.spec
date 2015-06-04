Name:       capi-media-thumbnail-util
Summary:    A media thumbnail util library in SLP C API
Version: 0.1.0
Release:    1
Group:      System/Libraries
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
A media thumbnail util  library in SLP C API

%package devel
Summary:  A media thumbnail util  library in SLP C API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel
A media thumbnail util  library in SLP C API

%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
make %{?jobs:-j%jobs}

%install
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-media-thumbnail-util.manifest
%{_libdir}/libcapi-media-thumbnail-util.so
%{_datadir}/license/%{name}

%files devel
%{_includedir}/media/*.h
%{_libdir}/pkgconfig/capi-media-thumbnail-util.pc
