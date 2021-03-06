// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
#include "ColorMap.h"
#include <string>

typedef  struct {unsigned char r,g, b;} RGB;
#define RGBSIZE(table) (sizeof(table)/sizeof(table[0]))

const char* builtinNames[] = {
	"default",
	"rainbow",
	"eldoraDbz",
	"spolDbz",
	"eldoraVel",
	"spolVel",
	"spolDiv"
};

static RGB
rainbowRGB[] = {
	{ 0, 0, 0}, { 84, 0, 155}, { 45, 0, 232}, { 0, 30, 255},
	{ 0, 114, 255}, { 0, 199, 255}, { 0, 255, 220}, { 0, 255, 135},
	{ 0, 255, 55}, { 73, 255, 0}, { 157, 255, 0}, { 246, 255, 0}, 
	{ 255, 224, 0}, { 255, 136, 0}, { 255, 53, 0}, { 255, 255, 255}
};


// eldora dbZ
static RGB
eldoraDbzRGB[] = {
	{60, 60, 60}, {0, 69, 0}, {0, 101, 10},
	{0, 158, 30}, {0, 177, 59}, {0, 205, 116}, {0, 191, 150},
	{0, 159, 206}, {8, 127, 219}, {28, 71, 232}, {56, 48, 222},
	{110, 13, 198}, {144, 12, 174}, {200, 15, 134}, {196, 67, 134},
	{192, 100, 135}, {191, 104, 101}, {190, 108, 68}, {210, 136, 59},
	{250, 196, 49}, {254, 217, 33}, {254, 250, 3}, {254, 221, 28},
	{254, 154, 88}, {254, 130, 64}, {254, 95, 5}, {249, 79, 8},
	{253, 52, 28}, {200, 117, 104}, {215, 183, 181}, {210, 210, 210},
	{151, 151, 0}, {219, 219, 0}
};

// eldora velocity
static RGB
eldoraVelocityRGB[] = {
	{255, 0,   255}, {242, 0,   254}, {222, 0,   254},
	{200, 0,   254}, {186, 0,   254}, {175, 0,   253}, {165, 0,   252},
	{139, 0,   248}, {113, 1,   242}, {71,  19,  236}, {50,  75,  229},
	{0,   110, 229}, {0,   182, 228}, {4,   232, 152}, {151, 151, 0}, 
	{2,   116,  76}, {125, 125, 125}, {217, 149, 49}, {238, 184, 31},
	{252, 218, 18},   {219, 219, 0},  {230, 218, 33},  {230, 177, 100},
	{230, 145, 150}, {230, 131, 131}, {230, 108, 108},  {230, 75,  75}, 
	{254, 120,  0},   {254, 90,  0},   {225, 0, 0},   {200, 0, 0},
	{175, 0,   0}, {150, 0,   0},
};

/*      spol NCAR official reflectivity color map */
static RGB
spolDbzRGB[] = {
	{0,0,0},{60,60,60},{0,69,0},{0,101,10},
	{0,158,30},{0,177,59},{0,205,116},{0,191,150},
	{0,159,206},{8,127,219},{28,71,232},{56,48,222},
	{110,13,198},{144,12,174},{200,15,134},{196,67,134},
	{192,100,135},{191,104,101},{190,108,68},{210,136,59},
	{250,196,49},{254,217,33},{254,250,3},{254,221,28},
	{254,154,88},{254,130,64},{254,95,5},{249,79,8},
	{253,52,28},{200,117,104},{215,183,181},{210,210,210}
};

/*      spol NCAR official divergence color map */
static RGB
spolDivRGB[] = {
	{0,0,0},{254,0,254},{253,0,254},{248,0,254},
	{222,0,254},{186,0,254},{175,0,253},{165,0,252},
	{139,0,248},{113,1,242},{71,19,236},{19,55,229},
	{0,110,229},{0,182,228},{4,232,152},
	/*  {2,116,76},  */
	{125,125,125},{125,125,125},{125,125,125},
	/*  {226,193,133},  */
	{217,149,49},{238,184,31},
	{252,218,18},{254,218,33},{254,177,100},{254,145,150},
	{254,131,131},{254,108,58},{254,93,7},{254,86,0},
	{254,55,0},{254,13,0},{254,0,0},{255,0,0},{0,0,0}
};

/*      spol NCAR official velocity color map */
static RGB
spolVelocityRGB[] = {
	{0,0,0},{254,0,254},{253,0,254},{248,0,254},
	{222,0,254},{186,0,254},{175,0,253},{165,0,252},
	{139,0,248},{113,1,242},{71,19,236},{19,55,229},
	{0,110,229},{0,182,228},{4,232,152},{2,116,76},
	{125,125,125},{226,193,133},{217,149,49},{238,184,31},
	{252,218,18},{254,218,33},{254,177,100},{254,145,150},
	{254,131,131},{254,108,58},{254,93,7},{254,86,0},
	{254,55,0},{254,13,0},{254,0,0},{255,0,0},{0,0,0}
};


/**********************************************************/
ColorMap::ColorMap()
{
	*this = ColorMap(0.0, 1.0);
}
/**********************************************************/
ColorMap::ColorMap(double minRange, 
				   double maxRange):
_minRange(minRange),
_maxRange(maxRange),
_range(maxRange-minRange)
{ 
	int s = sizeof(rainbowRGB)/(sizeof(rainbowRGB[0])/sizeof(rainbowRGB[0].r));
	for (int i = 0; i < s; i++) {
		_red.push_back(rainbowRGB[i].r/255.0);
		_green.push_back(rainbowRGB[i].g/255.0);
		_blue.push_back(rainbowRGB[i].b/255.0);
	}

	_tableSize = _red.size();
}

/**********************************************************/
ColorMap::ColorMap(
				   double minRange,         ///< The minimum map range
				   double maxRange,         ///< The maximum map range
				   std::vector<int> red,  ///< A vector of red hues, ranging between 0 and 255
				   std::vector<int> green,///< A vector of green hues, ranging between 0 and 255
				   std::vector<int> blue  ///< A vector of blue hues, ranging between 0 and 255
				   )
{
	setMap(minRange, maxRange, red, blue, green);
}

/**********************************************************/
ColorMap::ColorMap(
				   double minRange,         ///< The minimum map range
				   double maxRange,         ///< The maximum map range
				   std::vector<std::vector<int> >colors
				   )
{
	std::vector<float> red;
	std::vector<float> green;
	std::vector<float> blue;

	// verify that the inner vectors are of length three. If
	// not, then ignore the colors vector and use our default one.
	for (unsigned int i = 0; i < colors.size(); i++) {
		if (colors[i].size() != 3) {
			red.resize(_red.size());
			green.resize(_red.size());
			blue.resize(_red.size());
			for (unsigned int j = 0; j < _red.size(); j++) {
				red[j]   = rainbowRGB[j].r/255.0;
				green[j] = rainbowRGB[j].g/255.0;
				blue[j]  = rainbowRGB[j].b/255.0;
				break;
			}
		}
	}

	// if the incoming colors passed the test, then create the rgb vectors
	if (red.size() == 0) {
		red.resize(colors.size());
		green.resize(colors.size());
		blue.resize(colors.size());
		for (unsigned int i = 0; i < colors.size(); i++) {
			red[i]  = colors[i][0]/255.0;
			green[i] = colors[i][1]/255.0;
			blue[i]  = colors[i][2]/255.0;
		}
	}

	setMap(minRange, maxRange, red, green, blue);
}

/**********************************************************/
ColorMap::ColorMap(
				   double minRange,         ///< The minimum map range
				   double maxRange,         ///< The maximum map range
				   std::vector<std::vector<float> >colors
				   )
{
	std::vector<float> red;
	std::vector<float> green;
	std::vector<float> blue;

	// verify that the inner vectors are of length three. If
	// not, then ignore the colors vector and use our default one.
	for (unsigned int i = 0; i < colors.size(); i++) {
		if (colors[i].size() != 3) {
			red.resize(_red.size());
			green.resize(_red.size());
			blue.resize(_red.size());
			for (unsigned int j = 0; j < _red.size(); j++) {
				red[j]   = rainbowRGB[j].r;
				green[j] = rainbowRGB[j].g;
				blue[j]  = rainbowRGB[j].b;
				break;
			}
		}
	}

	// if the incoming colors passed the test, then create the rgb vectors
	if (red.size() == 0) {
		red.resize(colors.size());
		green.resize(colors.size());
		blue.resize(colors.size());
		for (unsigned int i = 0; i < colors.size(); i++) {
			red[i]  = colors[i][0]/255.0;
			green[i] = colors[i][1]/255.0;
			blue[i]  = colors[i][2]/255.0;
		}
	}

	setMap(minRange, maxRange, red, green, blue);
}
/**********************************************************/
ColorMap::ColorMap(
				   double minRange,         ///< The minimum map range
				   double maxRange,         ///< The maximum map range
				   std::string builtinName  /// the builtin map name
				   )
{
	RGB* colors;
	int tableSize = 0;
	if (!builtinName.compare("eldoraVel")) {
		colors = &eldoraVelocityRGB[0];
		tableSize = RGBSIZE(eldoraVelocityRGB);
	} else {
		if (!builtinName.compare("spolVel")) { 
			colors = &spolVelocityRGB[0];
			tableSize = RGBSIZE(spolVelocityRGB);
		} else {
			if (!builtinName.compare("eldoraDbz")) {
				colors = &eldoraDbzRGB[0];
				tableSize = RGBSIZE(eldoraDbzRGB);
			} else {
				if (!builtinName.compare("spolDbz")) {
					colors = &spolDbzRGB[0];
					tableSize = RGBSIZE(spolDbzRGB);
				} else {
					if (!builtinName.compare("spolDiv")) {
						colors = &spolDivRGB[0];
						tableSize = RGBSIZE(spolDivRGB);
					} else {
						if (!builtinName.compare("rainbow")) {
							colors = &rainbowRGB[0];
							tableSize = RGBSIZE(rainbowRGB);
						} else {
							// rainbow will be our default map.
							colors = &rainbowRGB[0];
							tableSize = RGBSIZE(rainbowRGB);
						}
					}
				}
			}
		}
	}

	std::vector<float> red;
	std::vector<float> green;
	std::vector<float> blue;
	red.resize(tableSize);
	green.resize(tableSize);
	blue.resize(tableSize);

	for (int i = 0; i < tableSize; i++) {
		red[i]   = colors[i].r/255.0;
		green[i] = colors[i].g/255.0;
		blue[i]  = colors[i].b/255.0;
	}

	setMap(minRange, maxRange, red, green, blue);
}
/**********************************************************/
void
ColorMap::setMap(
				 double minRange,         ///< The minimum map range
				 double maxRange,         ///< The maximum map range
				 std::vector<int> red,  ///< A vector of red hues, ranging between 0 and 255
				 std::vector<int> green,///< A vector of green hues, ranging between 0 and 255
				 std::vector<int> blue  ///< A vector of blue hues, ranging between 0 and 255
				 )
{
	setRange(minRange, maxRange);

	_tableSize = red.size();
	if (_tableSize > green.size())
		_tableSize = green.size();
	if (_tableSize >  blue.size())
		_tableSize = blue.size();

	_red.clear();
	_blue.clear();
	_green.clear();

	for (unsigned int i = 0; i < _tableSize; i++) {
		_red.push_back(red[i]/255.0);
		_green.push_back(green[i]/255.0);
		_blue.push_back(blue[i]/255.0);
	}
}

/**********************************************************/
void
ColorMap::setMap(
				 double minRange,         ///< The minimum map range
				 double maxRange,         ///< The maximum map range
				 std::vector<float> red,  ///< A vector of red hues, ranging between 0 and 255
				 std::vector<float> green,///< A vector of green hues, ranging between 0 and 255
				 std::vector<float> blue  ///< A vector of blue hues, ranging between 0 and 255
				 )
{
	setRange(minRange, maxRange);

	_tableSize = red.size();
	if (_tableSize > green.size())
		_tableSize = green.size();
	if (_tableSize >  blue.size())
		_tableSize = blue.size();

	_red.clear();
	_blue.clear();
	_green.clear();

	for (unsigned int i = 0; i < _tableSize; i++) {
		_red.push_back(red[i]);
		_green.push_back(green[i]);
		_blue.push_back(blue[i]);
	}
}

/**********************************************************/
void
ColorMap::setRange(double minRange, double maxRange) {
	_minRange = minRange;
	_maxRange = maxRange;
	_range = maxRange - minRange;
}

/**********************************************************/
ColorMap::~ColorMap()
{
}

/**********************************************************/
std::vector<int>
ColorMap::red()
{
	std::vector<int> rd;
	rd.resize(_red.size());
	for (unsigned int i = 0; i < rd.size(); i++) 
		rd[i] = (int)(_red[i]*255.0);
	return rd;
}

/**********************************************************/
std::vector<int>
ColorMap::green()
{
	std::vector<int> grn;
	grn.resize(_green.size());
	for (unsigned int i = 0; i < grn.size(); i++) 
		grn[i] = (int)(_green[i]*255.0);
	return grn;
}

/**********************************************************/
std::vector<int>
ColorMap::blue()
{
	std::vector<int> blu;
	blu.resize(_blue.size());
	for (unsigned int i = 0; i < blu.size(); i++) 
		blu[i] = (int)(_blue[i]*255.0);
	return blu;
}

/**********************************************************/
double
ColorMap::rangeMin() 
{
	return _minRange;
}

/**********************************************************/
double
ColorMap::rangeMax() 
{
	return _maxRange;
}

/**********************************************************/
std::vector<std::string>
ColorMap::builtinMaps() {
	std::vector<std::string> result;
	for (unsigned int i = 0; i < sizeof(builtinNames)/sizeof(char*); i++) {
		result.push_back(std::string(builtinNames[i]));
	}
	return result;
}
/**********************************************************/
void ColorMap::dataColor(
        double data, int& red, int& green, int& blue) const {

    int index = (int)(_tableSize* (data - _minRange)/(_range));

    if (index < 0)
        index = 0;
    else if (index > (int)(_tableSize-1))
        index = _tableSize - 1;

    red = (int)(_red[index]*255);
    blue = (int)(_blue[index]*255);
    green = (int)(_green[index]*255);
}
/**********************************************************/
void ColorMap::dataColor(
        double data, float& red, float& green, float& blue) const {

    int index = (int)(_tableSize* (data - _minRange)/_range);

    if (index < 0)
        index = 0;
    else if (index > (int)(_tableSize-1))
        index = _tableSize - 1;

    red = _red[index];
    blue = _blue[index];
    green = _green[index];
}
/**********************************************************/
void ColorMap::dataColor(
        double data, double& red, double& green, double& blue) const {

    int index = (int)(_tableSize* (data - _minRange)/_range);

    if (index < 0)
        index = 0;
    else if (index > (int)(_tableSize-1))
        index = _tableSize - 1;

    red = _red[index];
    blue = _blue[index];
    green = _green[index];
}

