#include "Class/ClassField.h"

/// @brief �����N���X���ǂ�������
/// @param  ���肷��N���X���
/// @return ���ۃN���X�Ȃ̂ŏ��False
bool IClassField::IsA(const IClassField* _class) const
{
	return _class ? IsSameObjectTypePrivate(_class->GetObjectTypeInfo()) : false;
}

/// @brief ���̃N���X���w��̃N���X���p�����Ă��邩�ǂ���
/// @param  �w��̃N���X
/// @return ���ۃN���X�Ȃ̂ŏ��False
bool IClassField::IsSubclassOf(const IClassField* _class) const
{
	const IClassField* classField = _class;

	// While�񂵂Čp�����̃N���X�����ǂ�
	while (classField)
	{
		// ��v��������������True
		if (IsA(classField))
		{
			return true;
		}
		classField = classField->GetSuper();
	}

	return false;
}

/// @brief �e�N���X�擾
/// @return �e�̃N���X���
const IClassField* IClassField::GetSuper() const
{
	return nullptr;
}

/// @brief �I�u�W�F�N�g��TypeInfo�擾
/// @return �I�u�W�F�N�g��TypeInfo
const std::type_info* IClassField::GetObjectTypeInfo() const
{
	return nullptr;
}

/// @brief TypeInfo���������̂��ǂ�������
/// @param _typeInfo ��r���TypeInfo
/// @return �����Ȃ�True
bool IClassField::IsSameObjectTypePrivate(const std::type_info* _opponentTypeInfo) const
{
	// TypeInfo�̈�v��r
	if (const std::type_info* info = GetObjectTypeInfo())
	{
		return _opponentTypeInfo ? *info == *_opponentTypeInfo : false;
	}

	// Nullptr���Ă���False
	return false;
}

/// @brief ��v�I�y���[�^�[
/// @param _class ��r��N���X
/// @return IsA�Ɠ���
bool IClassField::operator==(const IClassField* _class)
{
	return IsA(_class);
}
