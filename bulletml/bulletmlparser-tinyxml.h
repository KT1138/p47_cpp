/// BulletML �̃p�[�T�E�c���[ by tinyxml
/**
 * tinyxml�ɂ��BulletML�̃p�[�T
 */

#ifndef BULLETMLPARSER_TINYXML_H_
#define BULLETMLPARSER_TINYXML_H_

#include <string>

#include "bulletmlcommon.h"

#include "tinyxml/tinyxml.h"

class BulletMLNode;

class BulletMLParserTinyXML : public BulletMLParser {
public:
    DECLSPEC BulletMLParserTinyXML(const char* filename);
    DECLSPEC virtual ~BulletMLParserTinyXML();

    DECLSPEC virtual void parse();

private:
	void parseImpl(TiXmlDocument& doc);

protected:
    void getTree(TiXmlNode* node);
    void translateNode(TiXmlNode* node);

private:
    BulletMLNode* curNode_;
};

#endif // ! BULLETMLPARSER_TINYXML_H_
