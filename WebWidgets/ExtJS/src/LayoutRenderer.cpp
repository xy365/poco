//
// LayoutRenderer.cpp
//
// $Id: //poco/Main/WebWidgets/ExtJS/src/LayoutRenderer.cpp#5 $
//
// Library: ExtJS
// Package: Core
// Module:  LayoutRenderer
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/WebWidgets/ExtJS/LayoutRenderer.h"
#include "Poco/WebWidgets/ExtJS/FormRenderer.h"
#include "Poco/WebWidgets/ExtJS/Utility.h"
#include "Poco/WebWidgets/Layout.h"
#include "Poco/WebWidgets/Frame.h"
#include "Poco/WebWidgets/Panel.h"


namespace Poco {
namespace WebWidgets {
namespace ExtJS {


LayoutRenderer::LayoutRenderer()
{
}


LayoutRenderer::~LayoutRenderer()
{
}


void LayoutRenderer::renderLayoutHead(const Layout* pLayout, const RenderContext& context, std::ostream& ostr, const std::string& layoutId, const std::string& layoutConfig)
{
	poco_assert_dbg(pLayout != 0);
	Renderable::ID id(0);
	View::Ptr ptrParent = pLayout->parent();
	if (!(ptrParent && (ptrParent.cast<Frame>() || ptrParent.cast<Panel>())))
	{
		// the parent is not a panel 
		// assume that the direct parent is a panel
		ostr << "new Ext.Panel({border:false,bodyBorder:false,";
		renderParameters(pLayout, context, ostr, layoutId, layoutConfig);
		ostr << "})";
	}
	else
	{
		renderParameters(pLayout, context, ostr, layoutId, layoutConfig);
	}
}



void LayoutRenderer::renderBody(const Renderable* pRenderable, const RenderContext& context, std::ostream& ostr)
{
}


void LayoutRenderer::renderParameters(const Layout* pLayout, const RenderContext& context, std::ostream& ostr, const std::string& layoutId, const std::string& layoutConfig)
{
	poco_assert_dbg(pLayout != 0);
	bool writeComma = false;
	if (pLayout->getWidth() > 0)
		ostr << "width:" << pLayout->getWidth() << ",";
	if (!layoutId.empty())
	{
		ostr << "layout:'" << layoutId << "'";
		writeComma = true;
	}
	if (!layoutConfig.empty())
	{
		if (writeComma)
			ostr << ",layoutConfig:" << layoutConfig;
		else
			ostr << ",layoutConfig:" << layoutConfig;
		writeComma = true;
	}
	if (writeComma)
		ostr << ",items:[";
	else
		ostr << "items:[";
	visitChildren(pLayout, context, ostr);
	ostr << "]";
}


void LayoutRenderer::visitChildren(const Layout* pLayout, const RenderContext& context, std::ostream& ostr)
{
	ContainerView::ConstIterator it = pLayout->begin();
	for (; it != pLayout->end(); ++it)
	{
		if (it != pLayout->begin())
			ostr << ",";
		if (*it)
		{
			//horizontallayout works only when children are panels
			ostr << "{xtype:'panel',items:";
			(*it)->renderHead(context, ostr);
			ostr << "}";
		}
		else
			ostr << "{}";
		
	}
}


} } } // namespace Poco::WebWidgets::ExtJS