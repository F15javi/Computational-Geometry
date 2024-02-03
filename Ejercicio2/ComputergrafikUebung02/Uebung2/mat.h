#ifndef _MAT_H_
#define _MAT_H_

template <class T, unsigned SIZE> class CVector;

// template square matrix class for SIMPLE data types 
template <class T, unsigned SIZE> class CMatrix 
{
public:

	CMatrix<T, SIZE> () 
	{
		for (int j=0; j<SIZE; j++) {
			for (int i=0; i<SIZE; i++) {
				m_aatData[i][j] = T(0);
			}
		}
	}

	~CMatrix<T, SIZE> () 
	{	// nothing to do here ...
	}
	void setData(const T aatData[SIZE][SIZE])
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				m_aatData[i][j] = aatData[i][j];


			}
		}
	}
	
	CMatrix<T, SIZE> (const T aatData[SIZE][SIZE]) 
	{
		for (int j=0; j<SIZE; j++) {
			for (int i=0; i<SIZE; i++) {
				m_aatData[i][j] = aatData[i][j];
			}
		}
	}

	CMatrix<T, SIZE> (const CMatrix<T, SIZE> &mat) 
	{
		for (int j=0; j<SIZE; j++) {
			for (int i=0; i<SIZE; i++) {
				m_aatData[i][j] = mat.m_aatData[i][j];
			}
		}
	}

	T &operator () (unsigned i, unsigned j) 
	{
		if (i>=SIZE) i = SIZE-1;
		if (j>=SIZE) j = SIZE-1;
		return m_aatData[i][j];
	}

	T operator () (unsigned i, unsigned j) const 
	{
		if (i>=SIZE) i = SIZE-1;
		if (j>=SIZE) j = SIZE-1;
		return m_aatData[i][j];
	}

	// CMatrix<T, SIZE>operator + (const Matrix<T, SIZE> &mat)
	// CMatrix<T, SIZE>operator - (const Matrix<T, SIZE> &mat)
	// ...
	
	CMatrix<T, SIZE> operator * (const CMatrix<T, SIZE> &mat) {
		CMatrix<T, SIZE> buf;
		for (int i=0; i<SIZE; i++) // ZEILE i
			for (int j=0; j<SIZE; j++) // Spalte j
				for (int a=0; a<SIZE; a++) // a
					buf(i,j) += m_aatData[i][a] * mat(a,j);
		return buf;
	}

	CVector<T, SIZE> operator * (const CVector<T, SIZE> &vec) {
		CVector<T, SIZE> buf;
		for (int j=0; j<SIZE; j++) // SPALTE j
			for (int i=0; i<SIZE; i++) // ZEILE i
				buf(i) += m_aatData[i][j]*vec(j);
		return buf;
	}

private:

	T m_aatData[SIZE][SIZE];
};

// some common vector classes (abbr. names)
typedef CMatrix<float, 2> CMat2f;
typedef CMatrix<float, 3> CMat3f;
typedef CMatrix<float, 4> CMat4f;

typedef CMatrix<double, 2> CMat2d;
typedef CMatrix<double, 3> CMat3d;
typedef CMatrix<double, 4> CMat4d;

#endif;
