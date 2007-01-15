#ifndef __LDHTMLINVENTORY_H__
#define __LDHTMLINVENTORY_H__

#include <TCFoundation/TCObject.h>
#include <TCFoundation/TCStlIncludes.h>
#include <LDLoader/LDLPalette.h>
#include <stdio.h>

class LDPartsList;
class LDPartCount;
class LDLPalette;
class LDPreferences;

typedef enum
{
	LDPLCPart = 1,
	LDPLCDescription,
	LDPLCColor,
	LDPLCQuantity
} LDPartListColumn;

#include <TCFoundation/TCTypedValueArray.h>

typedef std::vector<LDPartListColumn> LDPartListColumnVector;
typedef std::map<LDPartListColumn, bool> LDPartListColumnBoolMap;

class LDHtmlInventory : public TCObject
{
public:
	LDHtmlInventory(void);

	void setShowModelFlag(bool value);
	bool getShowModelFlag(void) { return m_showModel; }
	void setExternalCssFlag(bool value);
	bool getExternalCssFlag(void) { return m_externalCss; }
	void setPartImagesFlag(bool value);
	bool getPartImagesFlag(void) { return m_partImages; }
	const LDPartListColumnVector &getColumnOrder(void) const
	{
		return m_columnOrder;
	}
	void setColumnOrder(const LDPartListColumnVector &value); 
	const char *getLastSavePath(void) { return m_lastSavePath.c_str(); }

	bool generateHtml(const char *filename, LDPartsList *partsList,
		const char *modelName);
protected:
	virtual ~LDHtmlInventory(void);
	virtual void dealloc(void);
	void writeHeader(FILE *file);
	void writeFooter(FILE *file);
	void writeTableHeader(FILE *file);
	void writeTableFooter(FILE *file);
	void writePartRow(FILE *file, const LDPartCount &partCount,
		LDLPalette *palette, const LDLColorInfo &colorInfo, int colorNumber);
	bool writeExternalCss(void);
	FILE *safeOpenCssFile(const std::string &cssFilename, bool &match);
	void writePartHeaderCell(FILE *file);
	void writeDescriptionHeaderCell(FILE *file);
	void writeColorHeaderCell(FILE *file);
	void writeQuantityHeaderCell(FILE *file);
	void writeHeaderCell(FILE *file, LDPartListColumn column);
	void writePartCell(FILE *file, const LDPartCount &partCount,
		LDLPalette *palette, const LDLColorInfo &colorInfo, int colorNumber);
	void writeDescriptionCell(FILE *file, const LDPartCount &partCount);
	void writeColorCell(FILE *file, LDLPalette *palette,
		const LDLColorInfo &colorInfo, int colorNumber);
	void writeQuantityCell(FILE *file, const LDPartCount &partCount,
		int colorNumber);
	void writeCell(FILE *file, LDPartListColumn column,
		const LDPartCount &partCount, LDLPalette *palette,
		const LDLColorInfo &colorInfo, int colorNumber);

	std::string m_modelName;
	LDPreferences *m_prefs;

	bool m_showModel;
	bool m_externalCss;
	bool m_partImages;
	std::string m_lastSavePath;
	int m_columns;
	LDPartListColumnVector m_columnOrder;
	LDPartListColumnBoolMap m_columnMap;

	static const char *sm_style;
	static const char *sm_cssHeader;
};

#endif // __LDHTMLINVENTORY_H__
