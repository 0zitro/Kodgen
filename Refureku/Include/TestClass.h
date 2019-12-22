#pragma once

#include "PropertyMacros.h"

#include <filesystem>
#include <vector>
#include <string>

namespace TestNamespace
{
	class Class1{};

	class RfrkClass(ClassProp1, ClassProp2[ClassSubProp21, ClassSubProp22], ClassProp3) TestClass final : public Class1
	{
		private:
			#pragma region Variables

			RfrkField(FieldProp1, FieldProp2[FieldSubProp21, FieldSubProp22], FieldProp3)
			const volatile int* const&	var1;

			#pragma endregion

		protected:
			RfrkField(FieldProp2[])
			class Hey*		var4 = nullptr;
	
		public:
			RfrkField(FieldProp1)
			int var2 : 1;

			#pragma region Methods

			RfrkMethod(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)
			virtual const volatile int* const& someMethod(int param1, class Hey* param2) const final;

			RfrkMethod(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)
			virtual int someMethod2(int param1, class Hey* param2) final
			{

			}

			int dsomeMethod3(int) noexcept;
			//int someMethosd3(int) override;
			virtual int someMethodd3(int) const;

			#pragma endregion

			RfrkField()
			float const		var3;
	};

	class TestClass2
	{
		private:
			#pragma region Variables

			RfrkMethod(var1 is following)
			int				var1 = 42;
			float			var2;

			#pragma endregion

			protected:

			public:
			#pragma region Methods

			RfrkMethod(int someMethod(int) is following)
			int someMethod(int);
			int dsomeMethod3(int) noexcept;
			virtual int someMethodd3(int) const;

			#pragma endregion
	};

	enum class RfrkEnum(Some enum) MyEnum
	{
		EVal1 RfrkEnumVal(heyhey) = 1 << 0,
		EVal2 = 1 << 1,
		Count
	};
}