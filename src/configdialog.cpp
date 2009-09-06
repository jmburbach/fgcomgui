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
#include "configdialog.hpp"
#include "configview.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QDialogButtonBox>

namespace FGComGui {

	ConfigDialog::ConfigDialog(QWidget* parent)
		: QDialog(parent)
	{
		setWindowIcon(QIcon(":data/images/fgcomgui_small.png"));
		setWindowTitle("Configure - FGComGui");

		QVBoxLayout* main_layout = new QVBoxLayout;
		main_layout->addWidget(new ConfigView(this));

		QFrame* line = new QFrame(this);
		line->setFrameShape(QFrame::HLine);
		line->setFrameShadow(QFrame::Sunken);
		main_layout->addWidget(line);

		QDialogButtonBox* button_box = new QDialogButtonBox(this);
		button_box->setOrientation(Qt::Horizontal);
		button_box->setStandardButtons(QDialogButtonBox::Close);
		main_layout->addWidget(button_box);
		connect(button_box, SIGNAL(accepted()),
				this, SLOT(accept()));
		connect(button_box, SIGNAL(rejected()),
				this, SLOT(reject()));

		setLayout(main_layout);
		adjustSize();
	};

	ConfigDialog::~ConfigDialog()
	{
	}

} // namespace FGComGui

