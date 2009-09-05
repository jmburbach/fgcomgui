import os
import subprocess

# get svn revision
BUILD_REV = subprocess.Popen(["svnversion", "-n", "."], stdout = subprocess.PIPE).communicate()[0]

# build options
opts = Variables("config.py")

# build env
env = Environment(env = os.environ, variables = opts)

# setup the options
opts.Add(PathVariable("prefix", "where to install files", "/usr/local", PathVariable.PathAccept))
opts.Add(BoolVariable("debug", "compile in debug mode", 0))
opts.Update(env)
opts.Save("config.py", env)
Help(opts.GenerateHelpText(env))

# setup env
env.Append(
	MOC_BIN = "moc-qt4", # qt meta object compiler
	RCC_BIN = "rcc", # qt resource compiler 
	CCFLAGS = [
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
		'FGCOM_GUI_PREFIX=\\"%s\\"' % env["prefix"],
		'FGCOM_GUI_BUILD=\\"%s\\"' % BUILD_REV
	],
	BUILDERS = {
		"MOC": Builder(action = "$MOC_BIN < $SOURCE > $TARGET"),
		"RCC": Builder(action = "$RCC_BIN $SOURCE > $TARGET")
	}
)

if env["debug"]:
	env.Append(CCFLAGS = [ "-g" ], CPPDEFINES = [ "DEBUG" ])
else:
	env.Append(CCFLAGS = [ "-O2" ], CPPDEFINES = [ "NDEBUG" ])

# where to build files
BuildDir("linux/build", "src")

# program source files
sources = [
	"linux/build/main.cpp",
	"linux/build/commonconfigview.cpp",
	"linux/build/appviewcontroller.cpp",
	"linux/build/model.cpp",
	"linux/build/configview.cpp",
	"linux/build/qt_resources.cpp",
	"linux/build/configdialog.cpp",
	"linux/build/aboutdialog.cpp"
]

# program headers that need moc'd
moc_headers = [
	"linux/build/commonconfigview.hpp",
	"linux/build/appviewcontroller.hpp",
	"linux/build/model.hpp",
	"linux/build/configview.hpp",
	"linux/build/aboutdialog.hpp"
]

# generate moc files 
for header in moc_headers:
	env.MOC(header + ".moc", header)

# generate resource file source
env.RCC("linux/build/qt_resources.cpp", "qt_resources.qrc")

# the program
fgcomgui = env.Program("linux/fgcomgui", sources)
Default(fgcomgui)

# install targets
install_targets = []

# for program
install_targets.append( env.Install("$prefix/bin", fgcomgui) )

# for license
install_targets.append( env.Install("$prefix/share/fgcomgui", "LICENSE.txt") )

# install targets for docs
doc_html = [ "docs/README.html" ]
doc_imgs = Glob("docs/images/*")
install_targets.append( env.Install("$prefix/share/doc/fgcomgui", doc_html) )
install_targets.append( env.Install("$prefix/share/doc/fgcomgui/images", doc_imgs) )

# install command
env.Alias("install", install_targets)

