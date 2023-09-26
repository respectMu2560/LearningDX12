#pragma once

// typeInfo
#include <typeinfo>

/// @brief �I�u�W�F�N�g�̃N���X���Z�߂����ۃN���X
class IClassField
{
public:

	/// @brief �����N���X���ǂ�������
	/// @param  ���肷��N���X���
	/// @return ���ۃN���X�Ȃ̂ŏ��False
	bool IsA(const IClassField* _class) const;

	/// @brief ���̃N���X���w��̃N���X���p�����Ă��邩�ǂ���
	/// @param  �w��̃N���X
	/// @return ���ۃN���X�Ȃ̂ŏ��False
	bool IsSubclassOf(const IClassField* _class) const;

	/// @brief �e�N���X�擾
	/// @return �e�̃N���X���
	virtual const IClassField* GetSuper() const;

protected:
	/// @brief �I�u�W�F�N�g��TypeInfo�擾
	/// @return �I�u�W�F�N�g��TypeInfo
	virtual const std::type_info* GetObjectTypeInfo() const;

	/// @brief TypeInfo���������̂��ǂ�������
	/// @param _typeInfo ��r���TypeInfo
	/// @return �����Ȃ�True
	bool IsSameObjectTypePrivate(const std::type_info* _opponentTypeInfo) const;

public:
	// operators

	/// @brief ��v�I�y���[�^�[
	/// @param _class ��r��N���X
	/// @return IsA�Ɠ���
	bool operator ==(const IClassField* _class);
};

/// @brief �I�u�W�F�N�g���̃e���v���[�g�N���X���p�����[�^�[
/// @tparam Type �I�u�W�F�N�g�̃N���X
/// @tparam Super �I�u�W�F�N�g�̌p�����N���X
template<typename Type, typename Super>
class TClassField : public IClassField
{
public:
	/// @brief Super�N���X�擾
	/// @return �I�u�W�F�N�g�̌p�����N���X��ClassField
	const IClassField* GetSuper() const override
	{
		return Super::StaticClass();
	}

private:
	/// @brief �I�u�W�F�N�g��TypeInfo�擾
	/// @return �I�u�W�F�N�g��TypeInfo
	const std::type_info* GetObjectTypeInfo() const override
	{
		static constexpr std::type_info&& TYPE_INFO = typeid(Type);
		return TYPE_INFO;
	}
};