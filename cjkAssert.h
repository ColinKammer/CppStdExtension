#pragma once
#include "MacroUtil.h"

namespace cjk
{
	void on_failed_assertion(const char* assertionMessage, const char* srcFile, unsigned srcLine);

}

namespace cjk::impl
{
	template <typename TargetT, typename SourceT>
	TargetT* assert_downcast(const char* srcFile, unsigned srcLine, SourceT* toCast)
	{
		TargetT* casted = dynamic_cast<TargetT*>(toCast);
		if (!casted)
			on_failed_assertion("Asserting downcast failed", srcFile, srcLine);
		return casted;
	}
	template <typename TargetT, typename SourceT>
	const TargetT* assert_downcast(const char* srcFile, unsigned srcLine, const SourceT* toCast)
	{
		const TargetT* casted = dynamic_cast<const TargetT*>(toCast);
		if (!casted)
			on_failed_assertion("Asserting downcast failed", srcFile, srcLine);
		return casted;
	}
	template <typename TargetT, typename SourceT>
	TargetT& assert_downcast(const char* srcFile, unsigned srcLine, SourceT& toCast)
	{
		return *assert_downcast<TargetT, SourceT>(srcFile, srcLine, &toCast);
	}
	template <typename TargetT, typename SourceT>
	const TargetT& assert_downcast(const char* srcFile, unsigned srcLine, const SourceT& toCast)
	{
		return *assert_downcast<TargetT, SourceT>(srcFile, srcLine, &toCast);
	}
}

#define CJK_ASSERT(expr, assertionMessage) \
    if (!(expr))                           \
        on_failed_assertion(assertionMessage, CJK_STRINGIFY(__FILE__), __LINE__);

#define CJK_ASSERT_UNREACHABLE(assertionMessage) \
    on_failed_assertion(assertionMessage, CJK_STRINGIFY(__FILE__), __LINE__);

#define CJK_ASSERT_NOTHROW(expr, assertionMessage) \
	try{\
		(void)(expr);\
	}\
	catch(...)\
	{\
		on_failed_assertion(assertionMessage, CJK_STRINGIFY(__FILE__), __LINE__);\
	}

#define CJK_ASSERT_DOWNCAST(targetType, toCast) \
    cjk::impl::assert_downcast<targetType>(CJK_STRINGIFY(__FILE__), __LINE__, toCast);