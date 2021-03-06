#include "RemoveLayerUndoAction.h"

#include "control/Control.h"
#include "gui/XournalView.h"
#include "model/Document.h"
#include "model/Layer.h"
#include "model/PageRef.h"

#include <i18n.h>

RemoveLayerUndoAction::RemoveLayerUndoAction(PageRef page, Layer* layer, int layerPos) : UndoAction("RemoveLayerUndoAction")
{
	XOJ_INIT_TYPE(RemoveLayerUndoAction);

	this->page = page;
	this->layer = layer;
	this->layerPos = layerPos;
}

RemoveLayerUndoAction::~RemoveLayerUndoAction()
{
	XOJ_CHECK_TYPE(RemoveLayerUndoAction);

	if (!this->undone)
	{
		// The layer was NOT undone, also NOT restored
		delete this->layer;
	}
	this->layer = NULL;

	XOJ_RELEASE_TYPE(RemoveLayerUndoAction);
}

string RemoveLayerUndoAction::getText()
{
	XOJ_CHECK_TYPE(RemoveLayerUndoAction);

	return _("Delete layer");
}

bool RemoveLayerUndoAction::undo(Control* control)
{
	XOJ_CHECK_TYPE(RemoveLayerUndoAction);

	this->page->insertLayer(this->layer, layerPos);
	Document* doc = control->getDocument();

	doc->lock();
	int id = doc->indexOf(this->page);
	doc->unlock();

	control->getWindow()->getXournal()->layerChanged(id);
	control->getWindow()->updateLayerCombobox();

	this->undone = true;

	return true;
}

bool RemoveLayerUndoAction::redo(Control* control)
{
	XOJ_CHECK_TYPE(RemoveLayerUndoAction);

	Document* doc = control->getDocument();

	doc->lock();
	this->page->removeLayer(this->layer);
	int id = doc->indexOf(this->page);
	doc->unlock();

	control->getWindow()->getXournal()->layerChanged(id);
	control->getWindow()->updateLayerCombobox();

	this->undone = false;

	return true;
}
