#pragma once

//TODO: study math
//Unused

struct Matrix4
{
public:
	Matrix4()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] = 0.0f;
			}
		}
	}
	Matrix4(float n)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] = n;
			}
		}
	}
	void Set(float n)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] = n;
			}
		}
	}
	void Identity()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] = i == j ? 1.0f : 0.0f;
			}
		}
	}
	void Ortho(float left, float right, float bottom, float top)
	{
		this->Set(1.0f);
		this->Matrix[0][0] = 2.0f / (right - left);
		this->Matrix[1][1] = 2.0f / (top - bottom);
		this->Matrix[2][2] = -1.0f;
		this->Matrix[3][0] = -(right + left) / (right - left);
		this->Matrix[3][0] = -(top + bottom) / (top - bottom);
	}

	void Transpose(const float mat[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] = mat[i][j];
			}
		}
	}
	void Transpose(const Matrix4& mat)
	{
		Transpose(mat.Matrix);
	}

	void Add(const float mat[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] += mat[i][j];
			}
		}
	}
	void Add(const Matrix4& mat)
	{
		Add(mat.Matrix);
	}

	void Substract(const float mat[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] -= mat[i][j];
			}
		}
	}
	void Substract(const Matrix4& mat)
	{
		Substract(mat.Matrix);
	}

	void Scale(float factor)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->Matrix[i][j] *= factor;
			}
		}
	}

	void Multiply(const float mat[4][4])
	{
		float result[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float num = 0;
				for (int k = 0; k < 4; k++) {
					num += this->Matrix[i][k] * mat[k][j];
				}
				result[i][j] = num;
			}
		}
		this->Transpose(result);
	}
	void Multiply(const Matrix4& mat)
	{
		Multiply(mat.Matrix);
	}

public:
	float Matrix[4][4];

};

