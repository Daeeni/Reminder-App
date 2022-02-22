import { ItemI } from './itemI';

export interface ListI {
  id: number;
  value: string;
  items: ItemI[];
}
