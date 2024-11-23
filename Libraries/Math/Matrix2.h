/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   ��̬����AHRS����
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __ROBO_LIB_MATRIX2_H__
#define __ROBO_LIB_MATRIX2_H__

#include "Libraries/Math/Vector2.h"

namespace robo_lib
{
template <typename T>

class Matrix2
{
public:
  robo_lib::Vector2<T> i, j; // i,jΪ��ά���������������

  // �޲ι�����ά����
  Matrix2<T>()
  {
    i.set(0, 0);
    j.set(0, 0);
  }

  // ͨ����ά��������ά����
  Matrix2<T>(const Matrix2<T>& c0)
  {
    i = c0.i;
    j = c0.j;
  }

  // ͨ������������ά����
  Matrix2<T>(const robo_lib::Vector2<T> i0, const robo_lib::Vector2<T> j0)
  {
    i = i0;
    j = j0;
  }

  // ͨ�������ÿ��Ԫ�ع���
  Matrix2<T>(const T ix, const T jx,
             const T iy, const T jy
            )
  {
    i.set(ix, iy);
    j.set(jx, jy);
  }

  // ��ȡ��������'x','y','z'
  robo_lib::Vector2<T> getRowVector(uint8_t row)
  {
    robo_lib::Vector2<T> dst;
    switch (row)
    {
    case 'x':
      dst.x = i.x;
      dst.y = j.x;
      break;
    case 'y':
      dst.x = i.y;
      dst.y = j.y;
      break;
    default:
      break;
    }
    return dst;
  }

  // ��ά�����ҳ�������ת��Ϊ����
  robo_lib::Vector2<T> translateVector(const robo_lib::Vector2<T>& vec) const
  {
    robo_lib::Vector2<T> dst;
    dst.x = vec.dotProduct(getRowVector('x'));
    dst.y = vec.dotProduct(getRowVector('y'));
    return dst;
  }

  // �ҳ���ά����
  Matrix2<T> translateMatrix(const Matrix2<T>& mat) const
  {
    Matrix2<T> dst;
    dst.i = *this->translateVector(mat.i);
    dst.j = *this->translateVector(mat.j);
    return dst;
  }

  // ��׼��
  void normalize()
  {
    this->i.normalize();
    this->j.normalize();
  }

  // ���ر�׼����ľ���
  Matrix2<T> normalized()
  {
    Matrix2<T> v = *this;
    v.normalize();
    return v;
  }

  // ����
  void inverse()
  {
    Matrix2<T> v(*this->j.y, -*this->j.x
                 *this->i.y, -*this->i.x);
    T scale = (*this->i.x) * (*this->j.y) - (*this->i.y) * (*this->j.x);
    return v.i.uniformScaling(scale);
  }

  // ���������ľ���
  Matrix2<T> inversed()
  {
    Matrix2<T> v(*this->j.y, -*this->j.x
                 *this->i.y, -*this->i.x);
    T scale = (*this->i.x) * (*this->j.y) - (*this->i.y) * (*this->j.x);
    *this = v.i.uniformScaling(scale);
  }
};

typedef Matrix2<int16_t>                Matrix2i;
typedef Matrix2<uint16_t>               Matrix2ui;
typedef Matrix2<int32_t>                Matrix2l;
typedef Matrix2<uint32_t>               Matrix2ul;
typedef Matrix2<float>                  Matrix2f;
typedef Matrix2<double>                 Matrix2d;
}
#endif