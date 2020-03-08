######################################################################
# Automatically generated by qmake (3.1) Fri Mar 6 21:06:22 2020
######################################################################

TEMPLATE = lib
TARGET = mebby
INCLUDEPATH += .
QT += websockets
CONFIG += c++14

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += \
	IMessage.h \
	IMessageCallback.h \
	IMessageResolver.h \
	MessageFilter.h \
	MessageFilterProxy.h \
	MessageResolver.h \
	MessageWriter.h

OTHER_FILES += \
	mebby.prf

headers.files = $${HEADERS}
headers.path = $$[QT_INSTALL_HEADERS]/Mebby

target.path = $$[QT_INSTALL_LIBS]

features.files = mebby.prf
features.path = $$[QMAKE_MKSPECS]/features

INSTALLS += headers target features