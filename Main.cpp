#include <QApplication>

#include "View/EditorWindowView.hpp"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	EditorWindowView editorWindowView;
	editorWindowView.showMaximized();

	return application.exec();
}
