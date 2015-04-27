#include <QFile>
#include <QDebug>
#include <QObject>
#include <QXmlStreamReader>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main (int argc, char** argv)
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
						("help,h", "produce help message")
						("file,f", po::value<std::string>(), "input xml file")
						;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

	if (! vm.count("file")) {
		std::cout << "ui file not provided" << std::endl;
		std::cout << desc << std::endl;
		return 1;
	}

	// Get the file as a QFile object
	QFile file(QString::fromStdString(vm["file"].as< std::string >()));

	if (!file.open(QIODevice::ReadOnly)) {
			std::cout << "Error reading file: " << vm["file"].as< std::string >() << std::endl;
			return 1;
		}

	// Init the xml using the QFile
	QXmlStreamReader xml(&file);

	xml.readNext();

	qDebug() << "root documentVersion: " << xml.documentVersion();
	qDebug() << "root isStartDocument: " << xml.isStartDocument();

	// Iterate over the xml file
	while (!xml.atEnd()) {
			QXmlStreamReader::TokenType tt = xml.readNext();

			if (tt == QXmlStreamReader::Characters
					&& !xml.isWhitespace()) {
				qDebug() << "   ::Characters: " << xml.text().toString();
			} else if (tt == QXmlStreamReader::StartElement) {
				qDebug() << "+::StartElement: " << xml.name();

				QXmlStreamAttributes attributes = xml.attributes();

				foreach(const QXmlStreamAttribute& attribute, attributes)
				{
					qDebug() << "      ::Attribute " << attribute.name().toString()
							<< " : " << attribute.value().toString();
				}

			} else if (tt == QXmlStreamReader::EndElement) {
				qDebug() << "-::EndElement: " << xml.name();
			} else if (tt == QXmlStreamReader::Characters
					&& xml.isWhitespace()) {
				// qDebug() << "] QXmlStreamReader::Characters with whitespaces.";
			}
	}

	file.close();

	return 0;
}
