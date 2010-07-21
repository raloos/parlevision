#include "InspectorWidget.h"
#include "ui_inspectorwidget.h"

#include <QtGui>
#include <list>

#include "PipelineElement.h"

using namespace plvgui;
using namespace plv;

InspectorWidget::InspectorWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::InspectorWidget),
    formContainer(0)
{
    ui->setupUi(this);
    nothingSelected();
}

InspectorWidget::~InspectorWidget()
{
    delete ui;
}

void InspectorWidget::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}    

void InspectorWidget::setTarget(plv::RefPtr<plv::PipelineElement> element)
{
    clearSelection();
    this->element = element;
    qDebug() << "Now inspecting " << element;

    ui->statusMsg->hide();

    std::list<QString> propertyNames;
    element->getConfigurablePropertyNames(propertyNames);

    this->formContainer = new QWidget(this);
    QFormLayout* form = new QFormLayout(this->formContainer);
    this->formContainer->setLayout(form);



    for(std::list<QString>::iterator itr = propertyNames.begin();
        itr != propertyNames.end(); ++itr)
    {
        QString propertyName = *itr;
        QVariant value = element->property(propertyName.toAscii());
        addRow(form, &propertyName, &value);
    }
//    ui->statusMsg->setText(element->getName());
//    this->setWindowTitle(element->getName());
    ui->verticalLayout->addWidget(formContainer);
}

void InspectorWidget::nothingSelected()
{
    clearSelection();
    ui->statusMsg->setText(tr("Nothing selected"));
    ui->statusMsg->show();
}

void InspectorWidget::multipleSelected()
{
    clearSelection();
    ui->statusMsg->setText(tr("Multiple items selected"));
    ui->statusMsg->show();
}

void InspectorWidget::clearSelection()
{
//    this->setWindowTitle("Inspector");
    this->element = 0;
    if(this->formContainer != 0)
    {
        ui->verticalLayout->removeWidget(this->formContainer);
        delete this->formContainer;
    }
    this->formContainer = 0;
}

void InspectorWidget::addRow(QFormLayout* form, QString* name, QVariant* value)
{
    switch(value->type())
    {
    case QVariant::Int:
        addRow(form, name, value->toInt());
        break;
    case QVariant::Bool:
        addRow(form, name, value->toBool());
        break;
    default:
        // substitute a non-editable string
        addRow(form, name, value->toString(), false);
    }
}

void InspectorWidget::addRow(QFormLayout* form, QString* name, int value)
{
    QSpinBox* spinBox = new QSpinBox(this);
    spinBox->setValue(value);
    form->addRow(new QLabel(*name, form->parentWidget()), spinBox);
}

void InspectorWidget::addRow(QFormLayout* form, QString* name, bool value)
{
    QCheckBox* checkBox = new QCheckBox(this);
    checkBox->setChecked(value);
    form->addRow(new QLabel(*name, form->parentWidget()), checkBox);
}

void InspectorWidget::addRow(QFormLayout* form, QString* name, QString value, bool editable)
{
    Q_UNUSED(editable)
    //TODO editable
    form->addRow(new QLabel(*name, form->parentWidget()), new QLabel(value, form->parentWidget()));
}
