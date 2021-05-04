#pragma once
/**
\file        Credit.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#ifndef CREDIT_H
#define CERDIT_H
namespace FindersEngine
{
    void CreditStateLoad(void);
    void CreditStateInit(void);
    void CreditStateUpdate(float dt);
    void CreditStateExit(void);
    void CreditStateUnload(void);
}
#endif