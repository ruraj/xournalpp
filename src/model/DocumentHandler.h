/*
 * Xournal++
 *
 * Document listener
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __DOCUMENTHANDLER_H__
#define __DOCUMENTHANDLER_H__

#include "DocumentChangeType.h"
#include <glib.h>

class DocumentListener;
class XojPage;

class DocumentHandler {
public:
	DocumentHandler();
	~DocumentHandler();

	void fireDocumentChanged(DocumentChangeType type);
	void firePageSizeChanged(int page);
	void firePageChanged(int page);
	void firePageInserted(int page);
	void firePageDeleted(int page);
	void firePageLoaded(XojPage * page);
	void firePageSelected(int page);
private:
	void addListener(DocumentListener * l);
	void removeListener(DocumentListener * l);

	GList * listener;

	friend class DocumentListener;
};

#endif /* __DOCUMENTHANDLER_H__ */