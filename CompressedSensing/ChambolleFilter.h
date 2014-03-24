/*========================================================================= 
 * 
 *  Copyright (c) 2013 Daniel Perry 
 * 
 *  MIT license 
 * 
 *=========================================================================*/ 
#ifndef ChambolleFilter_h 
#define ChambolleFilter_h 

// itk includes
#include "itkImage.h"
#include "itkImageToImageFilter.h"
#include "itkSmartPointer.h"

namespace imageprocessing
{
/**
 * ChambolleFilter
 *  Implementation of total variation.  Initially done for 
 *  CS 7640 - Advanced Image Processing, Spring 2013, University of Utah
 */
template< class TInputImage,
          class TOutputImage=TInputImage
        >
class ChambolleFilter:
  public itk::ImageToImageFilter<TInputImage,TOutputImage>
{
public:
  /**
   * Standard class typedefs
   */
  typedef ChambolleFilter Self;
  typedef itk::ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef itk::SmartPointer< Self > Pointer;
  typedef itk::SmartPointer< const Self > ConstPointer;

  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ChambolleFilter, ImageToImageFilter);

  /** Image type typedef support. */
  typedef TInputImage InputImageType;
  typedef TOutputImage OutputImageType;
  typedef typename OutputImageType::RegionType OutputImageRegionType;
  typedef typename InputImageType::SizeType ImageSizeType;

  /**
   * Step size for dual solution.
   */
  itkSetMacro(DualStepSize, float);
  itkGetConstMacro(DualStepSize, float);
  /**
   * Normalizing parameter - makes it less sensitive to step sizes,
   *   this parameter should be set according to the scales of gray levels.
   */
  itkSetMacro(Lambda, float);
  itkGetConstMacro(Lambda, float);
  /**
   * Max num of iterations
   */
  itkSetMacro(MaxIters, size_t);
  itkGetConstMacro(MaxIters, size_t);
  /**
   * num of iterations it took
   */
  itkSetMacro(Iters, size_t);
  itkGetConstMacro(Iters, size_t);
  /**
   * num of threads (zero means use max available)
   */
  itkSetMacro(ThreadCount, size_t);
  itkGetConstMacro(ThreadCount, size_t);
  virtual void SetNumberOfThreads(itk::ThreadIdType numThreads){ 
    m_ThreadCount = numThreads; 
    this->Superclass::SetNumberOfThreads(numThreads);
  }

protected:
  ChambolleFilter()
  :m_DualStepSize(1),
  m_Lambda(1),
  m_MaxIters(100),
  m_Iters(0),
  m_ThreadCount(0)
  {}

  virtual ~ChambolleFilter(){}
  void PrintSelf(std::ostream & os, itk::Indent indent) const;

  void GenerateData();

private:
  ChambolleFilter(const Self &); // not allowed
  void operator=(const Self &); // not allowed 

  float m_DualStepSize;
  float m_Lambda;
  size_t m_MaxIters;
  size_t m_Iters;
  size_t m_ThreadCount;
};
} // end namespace itk

#include "ChambolleFilter.hxx"

#endif
