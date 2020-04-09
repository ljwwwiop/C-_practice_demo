#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) {delete(p); (p)=nullptr;}}
#endif

void FactoryMain();
