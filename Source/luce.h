#ifndef __LUCE_H
#define __LUCE_H

#define LUCE_VERSION_MAJOR 0
#define LUCE_VERSION_MINOR 1
#define LUCE_VERSION_BUILD 0

#include <thread>
#include <list>
#include <map>
#include <iostream>
#include <fstream>

//#include "JuceHeader.h"
#include "Luce.h"

#if defined LUA52 || defined LUA53
#define LUA_COMPAT_MODULE
#else
#define lua_pushglobaltable(L) \
    lua_pushvalue(L, LUA_GLOBALSINDEX);
#endif

#include <lua.hpp>
namespace luce {

#include "LSelfKill.h"
#include "LBase.h"
#include "LuaO.h"
#include "LuceO.h"
#include "MainThread.h"
#include "luna5.h"

#include "LRefBase.h"

#include "base/LTime.h"
#include "base/LBigInteger.h"
#include "base/LRandom.h"
#include "base/LInputStream.h"
#include "base/LURL.h"

#include "LLookAndFeel.h"
#include "MyLookAndFeel.h"
//#include "LBase.h"
#include "LModifierKeys.h"
#include "LKeyPress.h"
#include "LMouseEvent.h"
#include "LColour.h"
#include "LAffineTransform.h"
#include "LImage.h"
#include "graphics/LPath.h"
#include "graphics/LPathStrokeType.h"
#include "graphics/LGraphics.h"
#include "graphics/LGlyphArrangement.h"
#include "graphics/LPositionedGlyph.h"
#include "graphics/LAttribute.h"
#include "graphics/LAttributedString.h"
#include "graphics/LGlyph.h"
#include "graphics/LRun.h"
#include "graphics/LLine.h"
#include "graphics/LTextLayout.h"
#include "graphics/LColourGradient.h"
#include "graphics/LFillType.h"
#include "LStretchableLayoutManager.h"
#include "LFont.h"
#include "LSourceDetails.h"
#include "LTimer.h"
#include "LHighResolutionTimer.h"

#include "LComponent.h"
#include "LViewport.h"
#include "LButton.h"
#include "LDocumentWindow.h"
#include "LMainComponent.h"
#include "LJComponent.h"
#include "LCallOutBox.h"
#include "LOpenGLShaderProgram.h"
#include "LOpenGLComponent.h"
#include "LJUCEApplication.h"
#include "LLabel.h"
#include "LTextButton.h"
#include "LToggleButton.h"
#include "LHyperlinkButton.h"
#include "LImageButton.h"
#include "LTextEditor.h"
//#include "LValueTree.h"
#include "LTreeView.h"
#include "LTreeViewItem.h"
#include "LStretchableLayoutResizerBar.h"
#include "LListBox.h"
#include "LComboBox.h"
#include "LSlider.h"
#include "LScrollBar.h"
#if JUCE_WINDOWS || JUCE_LINUX || JUCE_MAC 
#include "LSystemTrayIconComponent.h"
#endif
#include "drawable/LDrawable.h"
#include "drawable/LDrawableShape.h"
#include "drawable/LDrawablePath.h"
#include "drawable/LDrawableRectangle.h"
#include "drawable/LDrawableComposite.h"

#include "LOptions.h"
#include "LPopupMenu.h"

#include "extra/LColourSelector.h"
#if JUCE_MODAL_LOOPS_PERMITTED
#include "extra/LFileChooser.h"
#endif

#include "LConstants.h"

}

#endif // __LUCE_H
