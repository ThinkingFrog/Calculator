#pragma once
#include "Context.h"

typedef BaseOperation* (*LOADER) ();

int loadPlugins(Context &context);
int getExpression(Context &context);
int operateExpression(Context &context);
int calculate(Context &context);