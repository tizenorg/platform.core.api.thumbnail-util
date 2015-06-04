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

%if 0%{?sec_build_binary_debug_enable}
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"
%endif

cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
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
