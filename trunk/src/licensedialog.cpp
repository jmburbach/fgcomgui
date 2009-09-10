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
#include "licensedialog.hpp"
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QFile>
#include <QVBoxLayout>
#include <QIcon>
#include <QIODevice>
#include <QDir>

namespace FGComGui {

	LicenseDialog::LicenseDialog(QWidget* parent)
		: QDialog(parent)
	{
		setWindowIcon(QIcon(":data/images/fgcomgui_small.png"));
		setWindowTitle("License Agreement - FGComGui");

		QVBoxLayout* layout = new QVBoxLayout;
		setLayout(layout);

		QTextEdit* license_text = new QTextEdit(this);
		license_text->setReadOnly(true);
		license_text->setAlignment(Qt::AlignLeft);
		layout->addWidget(license_text);

		QDialogButtonBox* button_box = new QDialogButtonBox(this);
		button_box->setOrientation(Qt::Horizontal);
		button_box->setStandardButtons(QDialogButtonBox::Close);
		layout->addWidget(button_box);

		connect(button_box, SIGNAL(accepted()), 
				this, SLOT(accept()));
		connect(button_box, SIGNAL(rejected()),
				this, SLOT(reject()));

#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_LINUX
		QString filename = FGCOM_GUI_PREFIX"/share/fgcomgui/LICENSE.txt";
#else
		QDir d;
		QString filename = d.absoluteFilePath("LICENSE.txt");
#endif
		QFile file(filename);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			license_text->insertPlainText(file.readAll());
		else
			license_text->append("Failed to to load license file at: " + filename);

		license_text->moveCursor(QTextCursor::Start);

		resize(600, 600);
	}

} // namespace FGComGui

#include "licensedialog.hpp.moc"

