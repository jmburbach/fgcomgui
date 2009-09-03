BuildDir("linux/build", "src")

env = Environment(
	MOC_BIN = "moc-qt4",
	RCC_BIN = "rcc",
	CCFLAGS = [
		"-O2",
		"-pipe",
		"-Wall"
	],
	CPPPATH = [
		"/usr/include/qt4",
		"/usr/include/qt4/QtCore",
		"/usr/include/qt4/QtGui"
	],
	LIBPATH = [
		"/usr/lib"
	],
	LIBS = [
		"QtCore",
		"QtGui"
	],
	CPPDEFINES = [
		"LINUX",
	#	"NDEBUG"
	],	
	BUILDERS = {
		"MOC": Builder(action = "$MOC_BIN < $SOURCE > $TARGET"),
		"RCC": Builder(action = "$RCC_BIN $SOURCE > $TARGET")
	}
)

sources = [
	"linux/build/main.cpp",
	"linux/build/commonsettingsview.cpp",
	"linux/build/appviewcontroller.cpp",
	"linux/build/model.cpp",
	"linux/build/qt_resources.cpp"
]

moc_headers = [
	"linux/build/commonsettingsview.hpp",
	"linux/build/appviewcontroller.hpp",
	"linux/build/model.hpp"
]

for header in moc_headers:
	env.MOC(header + ".moc", header)

env.RCC("linux/build/qt_resources.cpp", "#/resources/qt_resources.qrc")

env.Program("linux/FGComGui", sources)

