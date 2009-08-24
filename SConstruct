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
		"NDEBUG"
	],	
	BUILDERS = {
		"MOC": Builder(action = "$MOC_BIN < $SOURCE > $TARGET"),
		"RCC": Builder(action = "$RCC_BIN $SOURCE > $TARGET")
	}
)

sources = [
	"linux/build/main.cpp",
	"linux/build/settingsview.cpp",
	"linux/build/appviewcontroller.cpp",
	"linux/build/settingsmodel.cpp",
	"linux/build/resources.cpp"
]

moc_headers = [
	"linux/build/settingsview.hpp",
	"linux/build/appviewcontroller.hpp"
]

for header in moc_headers:
	env.MOC(header + ".moc", header)

env.RCC("linux/build/resources.cpp", "#/resources/resources.qrc")

env.Program("linux/FGComGui", sources)

