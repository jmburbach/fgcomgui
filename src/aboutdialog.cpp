/* FGComGui - A simple gui frontend for fgcom.
 *
 * Copyright (C) 2009 Jacob Burbach <jmburbach@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 3, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "aboutdialog.hpp"
#include "licensedialog.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QIcon>
#include <QTabWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QDialogButtonBox>

#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
#define FGCOM_GUI_GPL_PATH "file:///LICENSE.txt"
#else
#define FGCOM_GUI_GPL_PATH "file:///"FGCOM_GUI_PREFIX"/share/fgcomgui/LICENSE.txt"
#endif


namespace FGComGui {

	AboutDialog::AboutDialog(QWidget* parent)
		: QDialog(parent)
		, m_title_widget(0)
		, m_about_page(0)
		, m_authors_page(0)
		, m_license_dialog(0)
	{
		setWindowTitle("About FGComGui");
		setWindowIcon(QIcon(":data/images/fgcomgui_small.png"));

		setup_title_widget();
		setup_about_page();
		setup_authors_page();
		
		QTabWidget* tab_widget = new QTabWidget(this);
		tab_widget->addTab(m_about_page, "&About");
		tab_widget->addTab(m_authors_page, "A&uthors");
		
		QDialogButtonBox* button_box = new QDialogButtonBox(this);
		button_box->setOrientation(Qt::Horizontal);
		button_box->setStandardButtons(QDialogButtonBox::Close);
		connect(button_box, SIGNAL(accepted()),
				this, SLOT(accept()));
		connect(button_box, SIGNAL(rejected()),
				this, SLOT(reject()));

		QVBoxLayout* main_layout = new QVBoxLayout;
		main_layout->addWidget(m_title_widget);
		main_layout->addWidget(tab_widget);
		main_layout->addWidget(button_box);
		setLayout(main_layout);
		adjustSize();
	}

	AboutDialog::~AboutDialog()
	{
	}

	void AboutDialog::setup_title_widget()
	{
		m_title_widget = new QWidget(this);
		QHBoxLayout* title_layout = new QHBoxLayout;
		m_title_widget->setLayout(title_layout);

		QLabel* image_label = new QLabel(this);
		image_label->setPixmap(QPixmap(":data/images/fgcomgui_large.png"));
		title_layout->addWidget(image_label);

		QLabel* title_label = new QLabel(this);
		title_label->setTextFormat(Qt::RichText);
		title_label->setText(
				"<html>"
				"	<head>"
				"		<style type=\"text/css\">"
				"			p {"
				"				padding: 0;"
				"				margin: 0;"
				"			}"
				"			p.large {"
				"				font-weight: bold;"
				"				font-size:	largs;"
				"				padding: 0;"
				"				margin: 0;"
				"			}"
				"			p.medium {"
				"				font-weight: bold;"
				"				font-size: medium;"
				"				padding: 0;"
				"				margin: 0;"
				"			}"
				"		</style>"
				"	</head>"
				"	<body>"
				"		<p class=\"large\">FGComGui</p>"
				"		<p class=\"medium\">svn revision "FGCOM_GUI_BUILD"</p>"
				"		<p>Using Qt "QT_VERSION_STR"</p>"
				"	</body>"
				"</html"
			);
		title_layout->addWidget(title_label);
		title_layout->addStretch();
	}

	void AboutDialog::setup_about_page()
	{
		m_about_page = new QWidget(this);
		QVBoxLayout* about_layout = new QVBoxLayout;
		m_about_page->setLayout(about_layout);

		QLabel* about_label = new QLabel(this);
		about_label->setTextFormat(Qt::RichText);
		about_label->setAlignment(Qt::AlignLeft|Qt::AlignTop);
		about_label->setText(
				"<html>"
				"	<head>"
				"		<style type=\"text/css\">"
				"			p,a {"
				"				margin: 0;"
				"				padding: 0;"
				"			}"
				"		</style>"
				"	</head>"
				"	<body>"
				"		<p>"
				"			This is FGComGui, a simple gui front end for FGCom<br />"
				"			<br />"
				"			Copyright (C) 2009 Jacob Burbach <jmburbach@gmail.com><br />"
				"			<br />"
				"			This program is free software: you can redistribute it and/or modify<br />"
				"			it under the terms of the <a href=\"file:///LICENSE.txt\">GNU General Public License</a>, version 3, as<br />"
				"			published by the Free Software Foundation.<br />"
				"			<br />"
				"			This program is distributed in the hope that it will be useful,<br />"
				"			but WITHOUT ANY WARRANTY; without even the implied warranty of<br />"
				"			MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the<br />"
				"			<a href=\"file:///LICENSE.txt\">GNU General Public License</a> for more details.<br />"
				"			<br />"
				"			Project page:<br />"
				"			<a href=\"http://code.google.com/p/fgcomgui\">http://code.google.com/p/fgcomgui</a><br />"
				"			<br />"
				"			Feedback:<br />"
				"			<a href=\"mailto:jmburbach@gmail.com\">jmburbach@gmail.com</a><br />"
				"			<br />"
				"			(Build Date: "__DATE__")"
				"		</p>"
				"	</body>"
				"</html>"
				);
		about_layout->addWidget(about_label);

		connect(about_label, SIGNAL(linkActivated(const QString&)),
				this, SLOT(handle_link_activated(const QString&)));
	}

	void AboutDialog::setup_authors_page()
	{
		m_authors_page = new QWidget(this);
		QVBoxLayout* authors_layout = new QVBoxLayout;
		m_authors_page->setLayout(authors_layout);

		QLabel* authors_label = new QLabel(this);
		authors_label->setTextFormat(Qt::RichText);
		authors_label->setAlignment(Qt::AlignLeft|Qt::AlignTop);
		authors_label->setText(
				"<html>"
				"	<head>"
				"		<style type=\"text/css\">"
				"			p,a {"
				"				margin: 0;"
				"				padding: 0;"
				"			}"
				"		</style>"
				"	</head>"
				"	<body>"
				"		<p>"
				"			Please use the <a href=\"http://code.google.com/p/fgcomgui/issues/list\">issue tracker</a> to report bugs."
				"			<br /><br />"
				"			Jacob Burbach <br />"
				"			<a href=\"mailto:jmburbach@gmail.com\">  jmburbach@gmail.com</a>"
				"		</p>"
				"	</body>"
				"</html>"
				);
		authors_layout->addWidget(authors_label);
		
		connect(authors_label, SIGNAL(linkActivated(const QString&)),
				this, SLOT(handle_link_activated(const QString&)));
	}

	void AboutDialog::handle_link_activated(const QString& url)
	{
		// intercept license, show dialog
		if (url == "file:///LICENSE.txt") {
			if (m_license_dialog == 0)
				m_license_dialog = new LicenseDialog(this);
			m_license_dialog->show();
			return;				
		}

		// otherwise let Qt figure it out
		QDesktopServices::openUrl(QUrl(url));
	}

} // namespace FGComGui

#include "aboutdialog.hpp.moc"

