      program myprogram                          
      implicit none

      real*8 oh2,xf
      integer unphys,war,ierr,iwar,nfc
      real*8 dsrdomega

      call dsinit
      call dsgivemodel_silveira_zee(0.3d0,1000.d0) ! lambda = 0.3, mdm = 1000
      call dsmodelsetup(unphys,iwar)
      oh2=dsrdomega(1,1,xf,ierr,iwar,nfc)
      write(*,*) 'Relic density, omega h^2 = ',oh2

      end

