#pragma once

#include "Color.h"
#include "Hittable.h"
#include "Camera.h"

/// <summary>
/// �����_�����O���s���B
/// </summary>
/// <param name="world">���̌Q</param>
/// <param name="background">�ǂ̕��̂ɂ��q�b�g���Ȃ��ꍇ�ɕԂ��F�Bnullable�����Anull�̏ꍇ�̓����_���[�œK���ɒ�`�����F��Ԃ��B</param>
/// <param name="camera">�J�����̏��</param>
/// <param name="width">��������摜�̉������̉�f��</param>
/// <param name="height">��������摜�̏c�����̉�f��</param>
/// <param name="maxDepth">���C�̔��˂�ǐՂ���ő吔</param>
/// <param name="sampleCount">�P��f������ɓ����郌�C�̐�</param>
/// <returns>�������ꂽ�摜(Color�̔z��B�{�֐���new����̂ŁA�Ăяo�����ŊJ�����K�v�B)</returns>
Color* render(Hittable* world, Color* background, const Camera& camera, int width, int height, int maxDepth, int sampleCount);
