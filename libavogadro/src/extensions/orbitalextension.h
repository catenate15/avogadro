/**********************************************************************
  OrbitalExtension - Extension for generating orbital cubes

  Copyright (C) 2008 Marcus D. Hanwell

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.sourceforge.net/>

  Avogadro is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#ifndef ORBITALEXTENSION_H
#define ORBITALEXTENSION_H

#include "basisset.h"
#include "orbitaldialog.h"

#include <avogadro/glwidget.h>
#include <avogadro/extension.h>

class QProgressDialog;
class QTime;

namespace Avogadro
{
  class BasisSet;
  class SlaterSet;

  class OrbitalExtension : public Extension
  {
  Q_OBJECT

  public:
    OrbitalExtension(QObject* parent = 0);
    virtual ~OrbitalExtension();

    virtual QString name() const { return QObject::tr("Orbitals"); }
    virtual QString description() const
    {
      return QObject::tr("Orbital cube generator");
    }

    virtual QList<QAction *> actions() const;

    virtual QString menuPath(QAction* action) const;

    virtual QUndoCommand* performAction(QAction *action, GLWidget *widget);

    void setMolecule(Molecule *molecule);

    bool loadBasis();

  private:
    GLWidget* m_glwidget;
    OrbitalDialog* m_orbitalDialog;
    QList<QAction *> m_actions;
    Molecule *m_molecule;
    BasisSet* m_basis;
    SlaterSet *m_slater;
    QString m_loadedFileName;
    QProgressDialog *m_progress, *m_progress2;
    QTime *m_timer1, *m_timer2;
    unsigned int m_currentMO;
    double m_stepSize;
    Eigen::Vector3d m_origin;
    Eigen::Vector3i m_steps;

    void calculateMO(int MO, const Eigen::Vector3d &origin,
                     const Eigen::Vector3i &steps, double stepSize);

  private Q_SLOTS:
    void calculateMO(int n);
    void calculateAll();
    void calculationDone();
    void calculation2Done();
    void calculationCanceled();
    void calculation2Canceled();
    void slaterDone();
    void slaterCanceled();

  };

  class OrbitalExtensionFactory : public QObject, public PluginFactory
  {
      Q_OBJECT
      Q_INTERFACES(Avogadro::PluginFactory)

      AVOGADRO_EXTENSION_FACTORY(OrbitalExtension,
          tr("Orbital Extension"),
          tr("Extension for calculating orbitals."))

  };

} // End namespace Avogadro

#endif
