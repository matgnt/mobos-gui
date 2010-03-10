# Check the Qt version. If QT_VERSION is not set, it is probably Qt 3.
isEmpty(QT_VERSION) {
    error("QT_VERSION not defined. This does not work with Qt 3.")
}
contains(QT_VERSION, ^4\.[0-6]\..*) {
    message("Cannot build with Qt version $$QT_VERSION")
    error("Use at least Qt 4.7")
}

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS = 3rdparty/qtDbus

