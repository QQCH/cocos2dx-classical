/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#include "support/component/CCComponentContainer.h"
#include "support/component/CCComponent.h"
#include "CCDirector.h"

NS_CC_BEGIN

CCComponentContainer::CCComponentContainer(CCNode *pNode)
: m_pComponents(nullptr)
, m_pOwner(pNode)
{
}

CCComponentContainer::~CCComponentContainer(void)
{
    CC_SAFE_RELEASE(m_pComponents);
}

CCComponent* CCComponentContainer::get(const char *pName) const
{
    CCComponent* pRet = nullptr;
    CCAssert(pName != nullptr, "Argument must be non-nil");
    do {
        CC_BREAK_IF(nullptr == pName);
        CC_BREAK_IF(nullptr == m_pComponents);
        pRet = dynamic_cast<CCComponent*>(m_pComponents->objectForKey(pName));
        
    } while (0);
    return pRet;
}

bool CCComponentContainer::add(CCComponent *pCom)
{
    bool bRet = false;
    CCAssert(pCom != nullptr, "Argument must be non-nil");
    CCAssert(pCom->getOwner() == nullptr, "Component already added. It can't be added again");
    do
    {
        if (m_pComponents == nullptr)
        {
            m_pComponents = CCDictionary::create();
            CC_SAFE_RETAIN(m_pComponents);
        }
        CCComponent *pComponent = dynamic_cast<CCComponent*>(m_pComponents->objectForKey(pCom->getName()));
        
        CCAssert(pComponent == nullptr, "Component already added. It can't be added again");
        CC_BREAK_IF(pComponent);
        pCom->setOwner(m_pOwner);
        m_pComponents->setObject(pCom, pCom->getName());
        pCom->onEnter();
        bRet = true;
    } while(0);
    return bRet;
}

bool CCComponentContainer::remove(const char *pName)
{
    bool bRet = false;
    CCAssert(pName != nullptr, "Argument must be non-nil");
    do 
    {        
        CC_BREAK_IF(!m_pComponents);
        CCObject* pRetObject = nullptr;
        CCDictElement *pElement = nullptr;
        HASH_FIND_PTR(m_pComponents->m_pElements, pName, pElement);
        if (pElement != nullptr)
        {
           pRetObject = pElement->getObject();
        }
        CCComponent *com = dynamic_cast<CCComponent*>(pRetObject);
        CC_BREAK_IF(!com);
        com->onExit();
        com->setOwner(nullptr);
        HASH_DEL(m_pComponents->m_pElements, pElement);
        CC_SAFE_RELEASE(pElement->getObject());
        CC_SAFE_DELETE(pElement);
        bRet = true;
    } while(0);
    return bRet;
 }

bool CCComponentContainer::remove(CCComponent *pCom)
{
    bool bRet = false;
    do 
    { 
        CC_BREAK_IF(!m_pComponents);
        CCDictElement *pElement = nullptr;
        CCDictElement *tmp = nullptr;
        HASH_ITER(hh, m_pComponents->m_pElements, pElement, tmp)
        {
            if (pElement->getObject() == pCom)
            {
                pCom->onExit();
                pCom->setOwner(nullptr);
                HASH_DEL(m_pComponents->m_pElements, pElement);
                CC_SAFE_RELEASE(pElement->getObject());
                CC_SAFE_DELETE(pElement);
                break;
            }
        }
        bRet = true;
    } while (0);
    return bRet;
}

void CCComponentContainer::removeAll()
{
    if (m_pComponents != nullptr)
    {
        CCDictElement *pElement, *tmp;
        HASH_ITER(hh, m_pComponents->m_pElements, pElement, tmp)
        {
            HASH_DEL(m_pComponents->m_pElements, pElement);
            ((CCComponent*)pElement->getObject())->onExit();
            ((CCComponent*)pElement->getObject())->setOwner(nullptr);
            CC_SAFE_RELEASE(pElement->getObject());
            CC_SAFE_DELETE(pElement);
        }
        m_pOwner->unscheduleUpdate();
    }
}

void CCComponentContainer::alloc(void)
{
    m_pComponents = CCDictionary::create();
    CC_SAFE_RETAIN(m_pComponents);
}

void CCComponentContainer::visit(float fDelta)
{
    if (m_pComponents != nullptr)
    {
        CCDictElement *pElement, *tmp;
        HASH_ITER(hh, m_pComponents->m_pElements, pElement, tmp)
        {
            ((CCComponent*)pElement->getObject())->update(fDelta);
        }
    }
}

bool CCComponentContainer::isEmpty() const
{
    return (bool)(!(m_pComponents && m_pComponents->count()));
}




NS_CC_END
